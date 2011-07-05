#include "Track.h"
#import "Artwork.h"
#import "async_macros.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

static Persistent<String> TRACK_CLASS_SYMBOL;

//Persistent<FunctionTemplate> Track::constructor_template;

void Track::Init(v8::Handle<Object> target) {
  HandleScope scope;

  // String Constants
  TRACK_CLASS_SYMBOL = NODE_PSYMBOL("Track");

  Local<FunctionTemplate> t = FunctionTemplate::New(New);
  track_constructor_template = Persistent<FunctionTemplate>::New(t);
  track_constructor_template->Inherit(item_constructor_template);
  track_constructor_template->SetClassName(TRACK_CLASS_SYMBOL);
  t->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(t, "artworks", Artworks);

  NODE_SET_PROTOTYPE_METHOD(t, "artist", Artist);

  target->Set(TRACK_CLASS_SYMBOL, track_constructor_template->GetFunction());
}

// JavaScript Constructor//////////////////////////////////////////////////////
v8::Handle<Value> Track::New(const Arguments& args) {
  HandleScope scope;

  Track* track = new Track();
  track->Wrap(args.This());
  return args.This();
}


// Artworks ///////////////////////////////////////////////////////////////////
// Readonly
v8::Handle<Value> Track::Artworks(const Arguments& args) {
  HandleScope scope;
  REQUIRE_CALLBACK_ARG;
  INIT(Track);
  GET_CALLBACK;
  BEGIN_ASYNC(EIO_Artworks, EIO_AfterArtworks);
}

int Track::EIO_Artworks(eio_req *req) {
  INIT_EIO_FUNC;
  iTunesTrack *item = (iTunesTrack *)ar->itemRef;
  SBElementArray *artworks = [item artworks];
  [artworks retain];
  // I would normally want to move these into an NSMutableDictionary before
  // returning to the main thread, however it seems as though these Artwork
  // instances don't return a 'persistentID', so we have no key to cache the
  // values off of...
  ar->result = artworks;
  FINISH_EIO_FUNC;
}

int Track::EIO_AfterArtworks(eio_req *req) {
  INIT_AFTER_FUNC;
  argv[0] = Null();
  SBElementArray *res = (SBElementArray *)ar->result;
  NSUInteger count = [res count];
  Local<Array> result = Array::New(count);
  iTunesArtwork *a;
  for (NSUInteger i = 0; i < count; i++) {
    a = [res objectAtIndex: i];
    [a retain];
    Local<Object> aWrap = artwork_constructor_template->GetFunction()->NewInstance();
    Artwork *aUnwrap = ObjectWrap::Unwrap<Artwork>(aWrap);
    aUnwrap->itemRef = a;
    result->Set(Integer::New(i), aWrap);
  }
  argv[1] = result;
  [res release];
  FINISH_AFTER_FUNC;
}

// Artist /////////////////////////////////////////////////////////////////////
v8::Handle<Value> Track::Artist(const Arguments& args) {
  HandleScope scope;
  INIT(Track);
  if (HAS_INPUT_ARG) {
    String::Utf8Value val(args[0]);
    char *input = (char *)malloc(strlen(*val) + 1);
    strcpy(input, *val);
    ar->input = input;
  } else {
    ar->input = NULL;
  }
  if (HAS_CALLBACK_ARG) {
    GET_CALLBACK;
  }
  BEGIN_ASYNC(EIO_Artist, EIO_AfterArtist);
}

int Track::EIO_Artist (eio_req *req) {
  INIT_EIO_FUNC;
  iTunesTrack *item = (iTunesTrack *)ar->itemRef;
  if (ar->input != NULL) {
    NSString *val = [NSString stringWithCString: (const char *)ar->input encoding: NSUTF8StringEncoding];
    [item setArtist: val];
  }
  NSString *str = [item artist];
  [str retain];
  ar->id = [str UTF8String];
  FINISH_EIO_FUNC;
}

int Track::EIO_AfterArtist (eio_req *req) {
  INIT_AFTER_FUNC;
  argv[0] = Null();
  argv[1] = String::New(ar->id);
  FINISH_AFTER_FUNC;
}

} // namespace node_iTunes
