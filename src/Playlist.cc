#include "Playlist.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> PLAYLIST_CLASS_SYMBOL;

void Playlist::Init(v8::Handle<Object> target) {
  HandleScope scope;

  // String Constants
  PLAYLIST_CLASS_SYMBOL = NODE_PSYMBOL("Playlist");

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  playlist_constructor_template = Persistent<FunctionTemplate>::New(t);
  playlist_constructor_template->Inherit(item_constructor_template);
  playlist_constructor_template->SetClassName(PLAYLIST_CLASS_SYMBOL);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  //NODE_SET_PROTOTYPE_METHOD(t, "run", GetVolume);
  //NODE_SET_METHOD(target, "createConnection", CreateConnection);

  target->Set(PLAYLIST_CLASS_SYMBOL, playlist_constructor_template->GetFunction());
}

// JavaScript Constructor /////////////////////////////////////////////////////
  v8::Handle<Value> Playlist::New(const Arguments& args) {
  HandleScope scope;

  Playlist* p = new Playlist();
  p->Wrap(args.This());
  return args.This();
}

} // namespace node_iTunes
