#include "Item.h"
#include "async_macros.h"
#include <unistd.h>

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> ITEM_CLASS_SYMBOL;

void Item::Init(v8::Handle<Object> target) {
  HandleScope scope;

  // String Constants
  ITEM_CLASS_SYMBOL = NODE_PSYMBOL("Item");

  // Set up the 'Item' base-class constructor template
  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  item_constructor_template = Persistent<FunctionTemplate>::New(t);
  item_constructor_template->SetClassName(ITEM_CLASS_SYMBOL);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(t, "container", Container);
  NODE_SET_PROTOTYPE_METHOD(t, "name", Name);

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


// Container //////////////////////////////////////////////////////////////////
// Readonly
v8::Handle<Value> Item::Container(const Arguments& args) {
  HandleScope scope;
  REQUIRE_CALLBACK_ARG;
  INIT(Item);
  GET_CALLBACK;
  BEGIN_ASYNC(EIO_Container, EIO_AfterContainer);
}

int Item::EIO_Container(eio_req *req) {
  INIT_EIO_FUNC;
  iTunesItem *item = (iTunesItem *)ar->itemRef;
  iTunesItem *container = [[item container] get];
  [container retain];
  ar->result = (void *)container;
  ar->id = [[container persistentID] UTF8String];
  FINISH_EIO_FUNC;
}

int Item::EIO_AfterContainer(eio_req *req) {
  INIT_AFTER_FUNC;
  // TODO: Error Handling
  argv[0] = Null();
  argv[1] = Item::WrapInstance((iTunesItem *)ar->result, ar->id);
  FINISH_AFTER_FUNC;
}


// Name //////////////////////////////////////////////////////////////////////
v8::Handle<Value> Item::Name(const Arguments& args) {
  HandleScope scope;
  INIT(Item);
  if (HAS_INPUT_ARG) {
    String::Utf8Value name(args[0]);
    char *input = (char *)malloc(strlen(*name) + 1);
    strcpy(input, *name);
    ar->input = input;
  } else {
    ar->input = NULL;
  }
  if (HAS_CALLBACK_ARG) {
    GET_CALLBACK;
  }
  BEGIN_ASYNC(EIO_Name, EIO_AfterName);
}

int Item::EIO_Name (eio_req *req) {
  INIT_EIO_FUNC;
  iTunesItem *item = (iTunesItem *)ar->itemRef;
  if (ar->input != NULL) {
    // set
    NSString *name = [NSString stringWithCString: (const char *)ar->input encoding: NSUTF8StringEncoding];
    [item setName: name];
  }
  // get
  NSString *str = [item name];
  if (str) {
    [str retain];
    ar->result = (void *)[str UTF8String];
  } else {
    NSError *error = [ar->itemRef lastError];
    NSLog(@"Got Error: %@", error);
  }
  FINISH_EIO_FUNC;
}

int Item::EIO_AfterName (eio_req *req) {
  INIT_AFTER_FUNC;
  // TODO: Error Handling
  argv[0] = Null();
  argv[1] = String::New((const char *)ar->result);
  FINISH_AFTER_FUNC;
}


} // namespace node_iTunes
