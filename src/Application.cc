#include "Application.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> APPLICATION_CLASS_SYMBOL;
static Persistent<String> HOST_SYMBOL;
static Persistent<String> USERNAME_SYMBOL;
static Persistent<String> PASSWORD_SYMBOL;

static Persistent<Object> NEW_CHECKER;

Persistent<FunctionTemplate> Application::constructor_template;

void Application::Init(v8::Handle<Object> target) {
  HandleScope scope;

  // String Constants
  APPLICATION_CLASS_SYMBOL = NODE_PSYMBOL("Application");
  HOST_SYMBOL = NODE_PSYMBOL("host");
  USERNAME_SYMBOL = NODE_PSYMBOL("username");
  PASSWORD_SYMBOL = NODE_PSYMBOL("password");

  // This Object is used in the Application JS constructor to ensure that the
  // user isn't calling 'new Application', but rather '.createConnection()'.
  NEW_CHECKER = Persistent<Object>::New(Object::New());

  // Set up the 'Application' constructor template
  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->SetClassName(APPLICATION_CLASS_SYMBOL);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  //NODE_SET_PROTOTYPE_METHOD(t, "runSync", GetVolumeSync);
  NODE_SET_PROTOTYPE_METHOD(t, "isRunningSync", IsRunningSync);
  NODE_SET_PROTOTYPE_METHOD(t, "quitSync", QuitSync);
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

  target->Set(APPLICATION_CLASS_SYMBOL, constructor_template->GetFunction());
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
   if (args.Length() != 1 || !NEW_CHECKER->StrictEquals(args[0]->ToObject())) {
    return ThrowException(Exception::TypeError(String::New("Use '.createConnection()' to get an Application instance")));
  }

  Application* hw = new Application();
  hw->Wrap(args.This());
  return args.This();
}

v8::Handle<Value> Application::IsRunningSync(const Arguments& args) {
  HandleScope scope;
  Application* it = ObjectWrap::Unwrap<Application>(args.This());
  iTunesApplication* iTunes = it->iTunesRef;
  v8::Handle<v8::Boolean> result = v8::Boolean::New([iTunes isRunning]);
  return scope.Close(result);
}

v8::Handle<Value> Application::QuitSync(const Arguments& args) {
  HandleScope scope;
  Application* it = ObjectWrap::Unwrap<Application>(args.This());
  iTunesApplication* iTunes = it->iTunesRef;
  [iTunes quit];
  return Undefined();
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

  if (args.Length() < 1) {
    return ThrowException(Exception::TypeError(String::New("A callback function is required")));
  }

  create_connection_request* ccr = (create_connection_request *) malloc(sizeof(struct create_connection_request));
  ccr->host = NULL;
  ccr->username = NULL;
  ccr->password = NULL;

  int cbIndex = 0;
  if (args[1]->IsFunction()) {
    cbIndex = 1;
    Local<Object> options = args[0]->ToObject();
    if (options->Has(HOST_SYMBOL)) {
      String::Utf8Value hostValue(options->Get(HOST_SYMBOL));
      char* hostStr = (char*)malloc(strlen(*hostValue) + 1);
      strcpy(hostStr, *hostValue);
      ccr->host = hostStr;
    } else {
      return ThrowException(Exception::TypeError(String::New("The 'host' property is required when an 'options' Object is given")));
    }
    if (options->Has(USERNAME_SYMBOL)) {
      String::Utf8Value unValue(options->Get(USERNAME_SYMBOL));
      char* unStr = (char*)malloc(strlen(*unValue) + 1);
      strcpy(unStr, *unValue);
      ccr->username = unStr;
    }
    if (options->Has(PASSWORD_SYMBOL)) {
      String::Utf8Value pwValue(options->Get(PASSWORD_SYMBOL));
      char* pwStr = (char*)malloc(strlen(*pwValue) + 1);
      strcpy(pwStr, *pwValue);
      ccr->password = pwStr;
    }
  }
  Local<Function> cb = Local<Function>::Cast(args[cbIndex]);
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
  if (ccr->host != NULL) {
    //printf("host: %s\n", ccr->host);
    NSString* urlStr = @"eppc://";
    if (ccr->username != NULL && ccr->password != NULL) {
      //printf("username: %s\n", ccr->username);
      //printf("password: %s\n", ccr->password);
      NSString* unString = [NSString stringWithCString: ((const char*)ccr->username) encoding: NSUTF8StringEncoding ];
      urlStr = [urlStr stringByAppendingString: [unString stringByAddingPercentEscapesUsingEncoding: NSASCIIStringEncoding ]];
      urlStr = [urlStr stringByAppendingString: @":" ];
      NSString* pwString = [NSString stringWithCString: ((const char*)ccr->password) encoding: NSUTF8StringEncoding ];
      urlStr = [urlStr stringByAppendingString: [pwString stringByAddingPercentEscapesUsingEncoding: NSASCIIStringEncoding ]];
      urlStr = [urlStr stringByAppendingString: @"@" ];
      free(ccr->password);
      free(ccr->username);
    }
    urlStr = [urlStr stringByAppendingString: [NSString stringWithCString: ((const char*)ccr->host) encoding: NSUTF8StringEncoding ]];
    urlStr = [urlStr stringByAppendingString: @"/iTunes" ];
    //NSLog(@"%@", urlStr);
    NSURL* url = [NSURL URLWithString: urlStr];
    ccr->iTunesRef = [SBApplication applicationWithURL: url];
    free(ccr->host);
  } else {
    // If no 'options' object was provided, then simply connect to the local
    // iTunes installation. No credentials are required for this mode.
    ccr->iTunesRef = [SBApplication applicationWithBundleIdentifier:@"com.apple.iTunes"];
  }
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
  v8::Handle<Value> constructor_args[1];
  constructor_args[0] = NEW_CHECKER;
  Local<Object> app = Application::constructor_template->GetFunction()->NewInstance(1, constructor_args);
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
