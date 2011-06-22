#define HAS_CALLBACK_ARG args[args.Length()-1]->IsFunction()

#define HAS_INPUT_ARG (!args[0]->IsFunction() && !args[0]->IsUndefined())

#define REQUIRE_CALLBACK_ARG  \
  if (!HAS_CALLBACK_ARG) {     \
    return ThrowException(Exception::TypeError(String::New("A callback function is required"))); \
  }


#define INIT(CLASS)                                                            \
  CLASS *item = ObjectWrap::Unwrap<CLASS>(args.This());                        \
  async_request *ar = (async_request *)malloc(sizeof(struct async_request));   \
  ar->input = NULL;                                                            \
  ar->itemRef = item->itemRef;                                                 \
  ar->mutex = &item->mutex;


#define GET_CALLBACK     \
  Local<Function> cb = Local<Function>::Cast(args[0]);            \
  ar->callback = Persistent<Function>::New(cb);                    \
  ar->thisRef = Persistent<Object>::New(args.This());


#define BEGIN_ASYNC(DO_FUNC, AFTER_FUNC)    \
  eio_custom(DO_FUNC, EIO_PRI_DEFAULT, AFTER_FUNC, ar);   \
  ev_ref(EV_DEFAULT_UC);        \
  return Undefined();


#define INIT_EIO_FUNC   \
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];   \
  async_request *ar = (async_request *)req->data;     \
  pthread_mutex_lock( ar->mutex );        \
  usleep(10 * 1000);


#define FINISH_EIO_FUNC    \
  pthread_mutex_unlock( ar->mutex );   \
  [pool drain];    \
  return 0;


#define INIT_AFTER_FUNC     \
  HandleScope scope;        \
  ev_unref(EV_DEFAULT_UC);  \
  async_request *ar = (async_request *)req->data;  \
  v8::Handle<Value> argv[2];


#define FINISH_AFTER_FUNC                  \
  TryCatch tryCatch;                            \
  ar->callback->Call(ar->thisRef, 2, argv);                 \
  if (tryCatch.HasCaught()) {                        \
    FatalException(tryCatch);                      \
  }      \
  ar->callback.Dispose();    \
  ar->callback.Clear();    \
  ar->thisRef.Dispose();     \
  ar->thisRef.Clear();     \
  free(ar);          \
  return 0;

