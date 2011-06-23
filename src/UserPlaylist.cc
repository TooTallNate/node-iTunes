#include "UserPlaylist.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> USER_PLAYLIST_CLASS_SYMBOL;

void UserPlaylist::Init(v8::Handle<Object> target) {
  HandleScope scope;

  // String Constants
  USER_PLAYLIST_CLASS_SYMBOL = NODE_PSYMBOL("UserPlaylist");

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  user_playlist_constructor_template = Persistent<FunctionTemplate>::New(t);
  user_playlist_constructor_template->Inherit(item_constructor_template);
  user_playlist_constructor_template->SetClassName(USER_PLAYLIST_CLASS_SYMBOL);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  target->Set(USER_PLAYLIST_CLASS_SYMBOL, user_playlist_constructor_template->GetFunction());
}

// JavaScript Constructor /////////////////////////////////////////////////////
  v8::Handle<Value> UserPlaylist::New(const Arguments& args) {
  HandleScope scope;

  UserPlaylist* p = new UserPlaylist();
  p->Wrap(args.This());
  return args.This();
}

} // namespace node_iTunes
