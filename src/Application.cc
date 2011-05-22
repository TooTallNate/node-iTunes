#include "Application.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> repo_class_symbol;

Persistent<FunctionTemplate> Application::constructor_template;

void Application::Init(v8::Handle<Object> target) {
  HandleScope scope;

  repo_class_symbol = NODE_PSYMBOL("Application");

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->SetClassName(repo_class_symbol);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  //NODE_SET_PROTOTYPE_METHOD(t, "runSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "quitSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "addSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "backTrackSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "convertSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "fastForwardSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "nextTrackSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "pauseSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "playOnceSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "playpauseSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "previousTrackSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "resumeSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "rewindSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "stopSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "updateSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "ejectSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "subscribeSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "updateAllPodcastsSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "updatePodcastSync", GetVolumeSync);
  //NODE_SET_PROTOTYPE_METHOD(t, "openLocationSync", GetVolumeSync);
  NODE_SET_PROTOTYPE_METHOD(t, "getVolumeSync", GetVolumeSync);
  NODE_SET_PROTOTYPE_METHOD(t, "setVolumeSync", SetVolumeSync);

  NODE_SET_METHOD(target, "createConnection", CreateConnection);

  target->Set(repo_class_symbol, constructor_template->GetFunction());
}


Application::Application() {
}

Application::~Application() {
  if (iTunesRef) {
    [iTunesRef release];
  }
  iTunesRef = nil;
}

v8::Handle<Value> Application::New(const Arguments& args) {
  HandleScope scope;
  Application* hw = new Application();
  hw->Wrap(args.This());
  return args.This();
}

v8::Handle<Value> Application::GetVolumeSync(const Arguments& args) {
  HandleScope scope;
  Application* it = ObjectWrap::Unwrap<Application>(args.This());
  iTunesApplication* iTunes = it->iTunesRef;
  Local<Integer> result = Integer::New([iTunes soundVolume]);
  return scope.Close(result);
}

v8::Handle<Value> Application::SetVolumeSync(const Arguments& args) {
  HandleScope scope;
  Application* it = ObjectWrap::Unwrap<Application>(args.This());
  iTunesApplication* iTunes = it->iTunesRef;
  int val = args[0]->ToInteger()->Int32Value();
  [iTunes setSoundVolume:val];
  Local<Integer> result = Integer::New([iTunes soundVolume]);
  return scope.Close(result);
}

// Begins asynchronously creating a new Application instance. This should be
// done on the thread pool, since the SBApplication constructor methods can
// potentially block for a very long time (especially if a modal dialog is
// raised for user credentials).
v8::Handle<Value> Application::CreateConnection(const Arguments& args) {
  HandleScope scope;

  create_connection_request* ccr = (create_connection_request *) malloc(sizeof(struct create_connection_request));
  ccr->host = NULL;
  ccr->username = NULL;
  ccr->password = NULL;

  Local<Function> cb = Local<Function>::Cast(args[0]);
  ccr->cb = Persistent<Function>::New(cb);

  eio_custom(CreateConnection_Do, EIO_PRI_DEFAULT, CreateConnection_After, ccr);
  ev_ref(EV_DEFAULT_UC);
  return Undefined();
}

// Creates the SBApplication instance. This is called on the thread pool since
// it can block for a long time.
int CreateConnection_Do (eio_req *req) {
  NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
  struct create_connection_request * ccr = (struct create_connection_request *)req->data;
  ccr->iTunesRef = [SBApplication applicationWithURL: [NSURL URLWithString: @"eppc://10.0.1.10/iTunes"]];
  [pool drain];
  return 0;
}

int CreateConnection_After (eio_req *req) {
  HandleScope scope;
  ev_unref(EV_DEFAULT_UC);
  struct create_connection_request * ccr = (struct create_connection_request *)req->data;
  Local<Value> argv[2];
  argv[0] = Local<Value>::New(Null());

  // We need to create an instance of the JS 'Application' class
  Local<Object> app = Application::constructor_template->GetFunction()->NewInstance();
  Application* it = ObjectWrap::Unwrap<Application>(app);
  it->iTunesRef = ccr->iTunesRef;
  argv[1] = app;

  //argv[2] = String::New(sr->name);
  TryCatch try_catch;
  ccr->cb->Call(Context::GetCurrent()->Global(), 2, argv);
  if (try_catch.HasCaught()) {
    FatalException(try_catch);
  }
  ccr->cb.Dispose();
  free(ccr);
  return 0;
}

} // namespace node_iTunes
