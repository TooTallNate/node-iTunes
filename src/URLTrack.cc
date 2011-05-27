#include "URLTrack.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> URL_TRACK_CLASS_SYMBOL;

//Persistent<FunctionTemplate> URLTrack::constructor_template;

void URLTrack::Init(v8::Handle<Object> target) {
  HandleScope scope;

  // String Constants
  URL_TRACK_CLASS_SYMBOL = NODE_PSYMBOL("URLTrack");

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  url_track_constructor_template = Persistent<FunctionTemplate>::New(t);
  url_track_constructor_template->Inherit(track_constructor_template);
  url_track_constructor_template->SetClassName(URL_TRACK_CLASS_SYMBOL);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  //NODE_SET_PROTOTYPE_METHOD(t, "runSync", GetVolumeSync);
  //NODE_SET_METHOD(target, "createConnection", CreateConnection);

  target->Set(URL_TRACK_CLASS_SYMBOL, url_track_constructor_template->GetFunction());
}

// Creates a new JS "Track" instance.
v8::Handle<Value> URLTrack::New(const Arguments& args) {
  HandleScope scope;

  URLTrack* track = new URLTrack();
  track->Wrap(args.This());
  return args.This();
}

/*v8::Handle<Value> Application::IsRunningSync(const Arguments& args) {
  HandleScope scope;
  Application* it = ObjectWrap::Unwrap<Application>(args.This());
  iTunesApplication* iTunes = it->iTunesRef;
  v8::Handle<v8::Boolean> result = v8::Boolean::New([iTunes isRunning]);
  return scope.Close(result);
}*/

} // namespace node_iTunes
