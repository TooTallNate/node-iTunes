#include "Item.h"
#include <unistd.h>

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> ITEM_CLASS_SYMBOL;

struct async_request {
  Persistent<Function> callback;
  Persistent<Object> thisRef;
  iTunesItem *itemRef;
  void *result;
  pthread_mutex_t *mutex;
};

void Item::Init(v8::Handle<Object> target) {
  HandleScope scope;

  // String Constants
  ITEM_CLASS_SYMBOL = NODE_PSYMBOL("Item");

  // Set up the 'Item' base-class constructor template
  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  item_constructor_template = Persistent<FunctionTemplate>::New(t);
  item_constructor_template->SetClassName(ITEM_CLASS_SYMBOL);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(t, "Name", Name);

  // The 'toString()' function uses sync I/O to get iTunes' stringified
  // version. The thought is that it's helpful for debugging/REPL, and probably
  // won't be used in production for anything.
  NODE_SET_PROTOTYPE_METHOD(t, "toString", ToString);

  target->Set(ITEM_CLASS_SYMBOL, item_constructor_template->GetFunction());
}


// C++ Constructor/Destructor ////////////////////////////////////////////////
Item::Item() {
  pthread_mutex_init(&mutex, NULL);
}

Item::~Item() {
  if (itemRef) {
    [itemRef release];
  }
  pthread_mutex_destroy(&mutex);
}

// JavaScript Constructor/////////////////////////////////////////////////////
v8::Handle<Value> Item::New(const Arguments& args) {
  HandleScope scope;
  Item* item = new Item();
  item->Wrap(args.This());
  return args.This();
}

// ToString //////////////////////////////////////////////////////////////////
v8::Handle<Value> Item::ToString(const Arguments& args) {
  HandleScope scope;
  Item *item = ObjectWrap::Unwrap<Item>(args.This());
  Local<String> str = String::New([[item->itemRef description] UTF8String]);
  return scope.Close(str);
}

// Name //////////////////////////////////////////////////////////////////////
v8::Handle<Value> Item::Name(const Arguments& args) {
  HandleScope scope;

  Item *item = ObjectWrap::Unwrap<Item>(args.This());

  async_request *ar = (async_request *)malloc(sizeof(struct async_request));
  ar->itemRef = item->itemRef;
  Local<Function> cb = Local<Function>::Cast(args[0]);
  ar->callback = Persistent<Function>::New(cb);
  ar->thisRef = Persistent<Object>::New(args.This());
  ar->mutex = &item->mutex;

  eio_custom(EIO_Name, EIO_PRI_DEFAULT, EIO_AfterName, ar);
  ev_ref(EV_DEFAULT_UC);

  return scope.Close(Undefined());
}

int Item::EIO_Name (eio_req *req) {
  async_request *ar = (async_request *)req->data;
  // TODO: Find a way around using an autorelease pool on the thread pool
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  pthread_mutex_lock( ar->mutex );
  usleep(10 * 1000);
  NSString *str = [ar->itemRef name];
  if (str) {
    [str retain];
    ar->result = (void *)[str UTF8String];
  } else {
    NSError *error = [ar->itemRef lastError];
    NSLog(@"Got Error: %@", error);
  }
  pthread_mutex_unlock( ar->mutex );
  [pool drain];
  return 0;
}

int Item::EIO_AfterName (eio_req *req) {
  HandleScope scope;
  ev_unref(EV_DEFAULT_UC);
  async_request *ar = (async_request *)req->data;

  TryCatch try_catch;
  v8::Handle<Value> argv[2];
  // TODO: Error Handling
  argv[0] = Null();
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
