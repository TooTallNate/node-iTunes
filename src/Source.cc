#include "Source.h"
#import "async_macros.h"

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

  NODE_SET_PROTOTYPE_METHOD(t, "kind", Kind);

  target->Set(SOURCE_CLASS_SYMBOL, source_constructor_template->GetFunction());
}

// JavaScript Constructor /////////////////////////////////////////////////////
  v8::Handle<Value> Source::New(const Arguments& args) {
  HandleScope scope;

  Source* s = new Source();
  s->Wrap(args.This());
  return args.This();
}

// Kind ///////////////////////////////////////////////////////////////////////
// Readonly
v8::Handle<Value> Source::Kind(const Arguments& args) {
  HandleScope scope;
  REQUIRE_CALLBACK_ARG;
  INIT(Source);
  GET_CALLBACK;
  BEGIN_ASYNC(EIO_Kind, EIO_AfterKind);
}

int Source::EIO_Kind(eio_req *req) {
  INIT_EIO_FUNC;
  iTunesSource *item = (iTunesSource *)ar->itemRef;
  iTunesESrc kind =  [item kind];
  switch (kind) {
    case iTunesESrcLibrary:
      ar->id = "Library";
      break;
    case iTunesESrcIPod:
      ar->id = "iPod";
      break;
    case iTunesESrcAudioCD:
      ar->id = "Audio CD";
      break;
    case iTunesESrcMP3CD:
      ar->id = "MP3 CD";
      break;
    case iTunesESrcDevice:
      ar->id = "Device";
      break;
    case iTunesESrcRadioTuner:
      ar->id = "Radio Tuner";
      break;
    case iTunesESrcSharedLibrary:
      ar->id = "Shared Library";
      break;
    default:
      ar->id = "Unknown";
      break;
  }
  FINISH_EIO_FUNC;
}

int Source::EIO_AfterKind(eio_req *req) {
  INIT_AFTER_FUNC;
  argv[0] = Null();
  argv[1] = String::New(ar->id);
  FINISH_AFTER_FUNC;
}

} // namespace node_iTunes
