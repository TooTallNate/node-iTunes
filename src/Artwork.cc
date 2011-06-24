#include "Artwork.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> ARTWORK_CLASS_SYMBOL;

void Artwork::Init(v8::Handle<Object> target) {
  HandleScope scope;

  // String Constants
  ARTWORK_CLASS_SYMBOL = NODE_PSYMBOL("Artwork");

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  artwork_constructor_template = Persistent<FunctionTemplate>::New(t);
  artwork_constructor_template->Inherit(item_constructor_template);
  artwork_constructor_template->SetClassName(ARTWORK_CLASS_SYMBOL);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  target->Set(ARTWORK_CLASS_SYMBOL, artwork_constructor_template->GetFunction());
}

// JavaScript Constructor /////////////////////////////////////////////////////
  v8::Handle<Value> Artwork::New(const Arguments& args) {
  HandleScope scope;

  Artwork* p = new Artwork();
  p->Wrap(args.This());
  return args.This();
}

} // namespace node_iTunes
