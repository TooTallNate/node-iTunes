#include "node_iTunesApplication.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> repo_class_symbol;

Persistent<FunctionTemplate> node_iTunesApplication::constructor_template;

void node_iTunesApplication::Init(v8::Handle<Object> target) {
  HandleScope scope;

  repo_class_symbol = NODE_PSYMBOL("iTunesApplication");

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  constructor_template = Persistent<FunctionTemplate>::New(t);
  constructor_template->SetClassName(repo_class_symbol);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(t, "getVolumeSync", GetVolumeSync);

  target->Set(repo_class_symbol, constructor_template->GetFunction());
}

node_iTunesApplication::node_iTunesApplication() {
  //iTunesRef = [SBApplication applicationWithBundleIdentifier:@"com.apple.iTunes"];
  iTunesRef = [SBApplication applicationWithURL: [NSURL URLWithString: @"eppc://10.0.1.10/iTunes"]];
}

node_iTunesApplication::~node_iTunesApplication() {
  delete iTunesRef;
}

v8::Handle<Value> node_iTunesApplication::New(const Arguments& args) {
  HandleScope scope;
  node_iTunesApplication* hw = new node_iTunesApplication();
  hw->Wrap(args.This());
  return args.This();
}

v8::Handle<Value> node_iTunesApplication::GetVolumeSync(const Arguments& args) {
  HandleScope scope;
  node_iTunesApplication* it = ObjectWrap::Unwrap<node_iTunesApplication>(args.This());
  iTunesApplication* iTunes = it->iTunesRef;
  Local<Integer> result = Integer::New([iTunes soundVolume]);
  return scope.Close(result);
}

} // namespace node_iTunes
