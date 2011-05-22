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

  target->Set(repo_class_symbol, constructor_template->GetFunction());
}

Application::Application(iTunesApplication* itunes) {
  //iTunesRef = [SBApplication applicationWithBundleIdentifier:@"com.apple.iTunes"];
  //iTunesRef = [SBApplication applicationWithURL: [NSURL URLWithString: @"eppc://10.0.1.10/iTunes"]];
  iTunesRef = itunes;
}

Application::~Application() {
  iTunesRef = nil;
}

v8::Handle<Value> Application::New(const Arguments& args) {
  HandleScope scope;
  iTunesApplication* itunes = [SBApplication applicationWithURL: [NSURL URLWithString: @"eppc://10.0.1.10/iTunes"]];
  Application* hw = new Application(itunes);
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
  iTunes.soundVolume = val;
  Local<Integer> result = Integer::New([iTunes soundVolume]);
  return scope.Close(result);
}

} // namespace node_iTunes
