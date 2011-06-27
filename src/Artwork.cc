#include <node/node_buffer.h>
#include "Artwork.h"
#include "async_macros.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> ARTWORK_CLASS_SYMBOL;

void free_artwork_data_callback(char *data, void *hint);

void Artwork::Init(v8::Handle<Object> target) {
  HandleScope scope;

  // String Constants
  ARTWORK_CLASS_SYMBOL = NODE_PSYMBOL("Artwork");

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  artwork_constructor_template = Persistent<FunctionTemplate>::New(t);
  artwork_constructor_template->Inherit(item_constructor_template);
  artwork_constructor_template->SetClassName(ARTWORK_CLASS_SYMBOL);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(t, "data", Data);

  target->Set(ARTWORK_CLASS_SYMBOL, artwork_constructor_template->GetFunction());
}

// JavaScript Constructor /////////////////////////////////////////////////////
  v8::Handle<Value> Artwork::New(const Arguments& args) {
  HandleScope scope;

  Artwork* p = new Artwork();
  p->Wrap(args.This());
  return args.This();
}

// Data ///////////////////////////////////////////////////////////////////////
v8::Handle<Value> Artwork::Data(const Arguments& args) {
  HandleScope scope;
  INIT(Artwork);
  if (HAS_CALLBACK_ARG) {
    GET_CALLBACK;
  }
  BEGIN_ASYNC(EIO_Data, EIO_AfterData);
}

// Gets the TIFF data representation by default.
// TODO: Add support for specifying format and compression level.
//   See here: http://borkware.com/quickies/one?topic=NSImage
int Artwork::EIO_Data(eio_req *req) {
  INIT_EIO_FUNC;
  iTunesArtwork *item = (iTunesArtwork *)ar->itemRef;
  NSImage *image = [item data];
  NSData *data = [image TIFFRepresentation];
  [data retain];
  ar->result = (void *)[data bytes];
  req->result = [data length];
  FINISH_EIO_FUNC;
}

int Artwork::EIO_AfterData(eio_req *req) {
  INIT_AFTER_FUNC;
  // TODO: Error handling
  argv[0] = Null();
  // Create the buffer.
  // http://sambro.is-super-awesome.com/2011/03/03/creating-a-proper-buffer-in-a-node-c-addon
  Buffer *slowBuffer = Buffer::New((char *)ar->result, req->result, free_artwork_data_callback, NULL);
  Local<Object> globalObj = Context::GetCurrent()->Global();
  Local<Function> bufferConstructor  = Local<Function>::Cast(globalObj->Get(String::New("Buffer")));
  v8::Handle<Value> constructorArgs[3] = { slowBuffer->handle_, Integer::New(req->result), Integer::New(0) };
  Local<Object> actualBuffer = bufferConstructor->NewInstance(3, constructorArgs);
  argv[1] = actualBuffer;
  FINISH_AFTER_FUNC;
}

void free_artwork_data_callback(char *data, void *hint) {
  NSLog(@"free_artwork_data_callback called, probably leaking memory!!!");
}


} // namespace node_iTunes
