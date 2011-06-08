#include "Item.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> ITEM_CLASS_SYMBOL;

struct async_request {
  Persistent<Function> callback;
  Persistent<Object> thisRef;
  Item *item;
  iTunesItem *itemRef;
  void *result;
};

//Persistent<FunctionTemplate> Item::constructor_template;

void Item::Init(v8::Handle<Object> target) {
  HandleScope scope;

  // String Constants
  ITEM_CLASS_SYMBOL = NODE_PSYMBOL("Item");

  // Set up the 'Item' base-class constructor template
  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  item_constructor_template = Persistent<FunctionTemplate>::New(t);
  item_constructor_template->SetClassName(ITEM_CLASS_SYMBOL);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(t, "getName", GetName);
  //NODE_SET_METHOD(target, "createConnection", CreateConnection);

  target->Set(ITEM_CLASS_SYMBOL, item_constructor_template->GetFunction());
}


Item::Item() {
}

Item::~Item() {
}

v8::Handle<Value> Item::New(const Arguments& args) {
  HandleScope scope;
  //if (args.Length() != 1 || !NEW_CHECKER->StrictEquals(args[0]->ToObject())) {
  //  return ThrowException(Exception::TypeError(String::New("Use '.createConnection()' to get an Application instance")));
  //}
  Item* item = new Item();
  item->Wrap(args.This());
  return args.This();
}

// GetName ////////////////////////////////////////////////////////////////////////
v8::Handle<Value> Item::GetName(const Arguments& args) {
  HandleScope scope;
  Item *item = ObjectWrap::Unwrap<Item>(args.This());

  async_request *ar = (async_request *)malloc(sizeof(struct async_request));
  ar->item = item;
  ar->itemRef = item->itemRef;
  Local<Function> cb = Local<Function>::Cast(args[0]);
  ar->callback = Persistent<Function>::New(cb);
  ar->thisRef = Persistent<Object>::New(args.This());

  eio_custom(EIO_GetName, EIO_PRI_DEFAULT, EIO_AfterGetName, ar);
  ev_ref(EV_DEFAULT_UC);

  return scope.Close(Undefined());
}

int Item::EIO_GetName (eio_req *req) {
  async_request *ar = (async_request *)req->data;
  // TODO: Find a way around using an autorelease pool on the thread pool
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  ar->result = (void *)[[ar->itemRef name] UTF8String];
  [pool drain];
  return 0;
}

int Item::EIO_AfterGetName (eio_req *req) {
  HandleScope scope;
  ev_unref(EV_DEFAULT_UC);
  async_request *ar = (async_request *)req->data;

  TryCatch try_catch;
  Local<Value> argv[2];
  argv[0] = Local<Value>::New(Null());
  argv[1] = String::New((const char *)ar->result);
  ar->callback->Call(ar->thisRef, 2, argv);

  if (try_catch.HasCaught()) {
    FatalException(try_catch);
  }
  ar->callback.Dispose();
  ar->thisRef.Dispose();
  free(ar);
  return 0;
}


} // namespace node_iTunes
