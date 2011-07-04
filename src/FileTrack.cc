#include "FileTrack.h"
#import "async_macros.h"

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

  NODE_SET_PROTOTYPE_METHOD(t, "location", Location);
  //NODE_SET_PROTOTYPE_METHOD(t, "refresh", Refresh;

  target->Set(FILE_TRACK_CLASS_SYMBOL, file_track_constructor_template->GetFunction());
}

// JavaScript Constructor /////////////////////////////////////////////////////
  v8::Handle<Value> FileTrack::New(const Arguments& args) {
  HandleScope scope;

  FileTrack* track = new FileTrack();
  track->Wrap(args.This());
  return args.This();
}


// Location ///////////////////////////////////////////////////////////////////
// Readonly
v8::Handle<Value> FileTrack::Location(const Arguments& args) {
  HandleScope scope;
  REQUIRE_CALLBACK_ARG;
  INIT(FileTrack);
  GET_CALLBACK;
  BEGIN_ASYNC(EIO_Location, EIO_AfterLocation);
}

int FileTrack::EIO_Location(eio_req *req) {
  INIT_EIO_FUNC;
  iTunesFileTrack *item = (iTunesFileTrack *)ar->itemRef;
  NSURL *location = [item location];
  // For NSURL, we will just return the Stringified "path", which can easily be
  // used with node's "fs" module...
  NSString *path = [location path];
  [path retain];
  ar->result = (void *)[path UTF8String];
  FINISH_EIO_FUNC;
}

int FileTrack::EIO_AfterLocation(eio_req *req) {
  INIT_AFTER_FUNC;
  argv[0] = Null();
  argv[1] = String::New((const char *)ar->result);
  FINISH_AFTER_FUNC;
}


} // namespace node_iTunes
