#include "Track.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> TRACK_CLASS_SYMBOL;

//Persistent<FunctionTemplate> Track::constructor_template;

void Track::Init(v8::Handle<Object> target) {
  HandleScope scope;

  // String Constants
  TRACK_CLASS_SYMBOL = NODE_PSYMBOL("Track");

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  track_constructor_template = Persistent<FunctionTemplate>::New(t);
  track_constructor_template->Inherit(item_constructor_template);
  track_constructor_template->SetClassName(TRACK_CLASS_SYMBOL);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  //NODE_SET_PROTOTYPE_METHOD(t, "runSync", GetVolumeSync);
  //NODE_SET_METHOD(target, "createConnection", CreateConnection);

  target->Set(TRACK_CLASS_SYMBOL, track_constructor_template->GetFunction());
}

// Convenience function that takes an iTunesTrack instance (or any subclass)
// and wraps it up into the proper JS class type, and returns it.
// TODO: Implement some kind of Object Cache, so if the same instance is
//       attempting to be wrapped again, then the same JS Object is returned.
// TODO: Move this to Item? Or it's own Wrapper file?
v8::Handle<Value> Track::WrapInstance(iTunesTrack* track) {
  HandleScope scope;

  NSString* className = NSStringFromClass([track class]);
  //NSLog(@"Class: %@", className);
  Local<Object> jsTrack;
  if ([className isEqualToString:@"ITunesURLTrack" ]) {
    jsTrack = url_track_constructor_template->GetFunction()->NewInstance();
  } else {
    jsTrack = track_constructor_template->GetFunction()->NewInstance();
  }
  Track* t = ObjectWrap::Unwrap<Track>(jsTrack);
  t->itemRef = track;
  return scope.Close(jsTrack);
}

// Creates a new JS "Track" instance.
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
