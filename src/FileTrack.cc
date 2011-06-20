#include "FileTrack.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> FILE_TRACK_CLASS_SYMBOL;

void FileTrack::Init(v8::Handle<Object> target) {
  HandleScope scope;

  // String Constants
  FILE_TRACK_CLASS_SYMBOL = NODE_PSYMBOL("FileTrack");

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  file_track_constructor_template = Persistent<FunctionTemplate>::New(t);
  file_track_constructor_template->Inherit(track_constructor_template);
  file_track_constructor_template->SetClassName(FILE_TRACK_CLASS_SYMBOL);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  //NODE_SET_PROTOTYPE_METHOD(t, "run", GetVolume);
  //NODE_SET_METHOD(target, "createConnection", CreateConnection);

  target->Set(FILE_TRACK_CLASS_SYMBOL, file_track_constructor_template->GetFunction());
}

// JavaScript Constructor /////////////////////////////////////////////////////
  v8::Handle<Value> FileTrack::New(const Arguments& args) {
  HandleScope scope;

  FileTrack* track = new FileTrack();
  track->Wrap(args.This());
  return args.This();
}

} // namespace node_iTunes
