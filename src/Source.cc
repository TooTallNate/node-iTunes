#include "Source.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> SOURCE_CLASS_SYMBOL;

void Source::Init(v8::Handle<Object> target) {
  HandleScope scope;

  // String Constants
  SOURCE_CLASS_SYMBOL = NODE_PSYMBOL("Source");

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  source_constructor_template = Persistent<FunctionTemplate>::New(t);
  source_constructor_template->Inherit(item_constructor_template);
  source_constructor_template->SetClassName(SOURCE_CLASS_SYMBOL);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  //NODE_SET_PROTOTYPE_METHOD(t, "run", GetVolume);
  //NODE_SET_METHOD(target, "createConnection", CreateConnection);

  target->Set(SOURCE_CLASS_SYMBOL, source_constructor_template->GetFunction());
}

// JavaScript Constructor /////////////////////////////////////////////////////
  v8::Handle<Value> Source::New(const Arguments& args) {
  HandleScope scope;

  Source* s = new Source();
  s->Wrap(args.This());
  return args.This();
}

} // namespace node_iTunes
