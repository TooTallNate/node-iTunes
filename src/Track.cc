#include "Track.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> TRACK_CLASS_SYMBOL;

Persistent<FunctionTemplate> Track::constructor_template;

void Track::Init(v8::Handle<Object> target) {
  HandleScope scope;

  // String Constants
  TRACK_CLASS_SYMBOL = NODE_PSYMBOL("Track");

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->Inherit(Item::constructor_template);
  constructor_template->SetClassName(TRACK_CLASS_SYMBOL);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  //NODE_SET_PROTOTYPE_METHOD(t, "runSync", GetVolumeSync);
  //NODE_SET_METHOD(target, "createConnection", CreateConnection);

  target->Set(TRACK_CLASS_SYMBOL, constructor_template->GetFunction());
}

v8::Handle<Value> Track::New(const Arguments& args) {
  HandleScope scope;

  Track* track = new Track();
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
