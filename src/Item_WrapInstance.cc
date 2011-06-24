#include <string>
#include <map>
#include "Item.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

// Object Cache. If an iTunesItem is wrapped that has the same 'persistentID'
// as another iTunesItem that's already been wrapped, then they're the same
// item, and the same JS Object instance should be returned.
static std::map<std::string, v8::Handle<Value> > cache;

// This callback function is called on any of the iTunesItem Persistent handles
// when there are no more references to the wrapper and it is about to be GC'd.
void weakItemCacheCallback(Persistent<Value> object, void *parameter) {
  std::string id((const char *)parameter);
  cache.erase(id);
  object.Dispose();
  object.Clear();
}

// Convenience function that takes an iTunesItem instance (or any subclass)
// and wraps it up into the proper JS class type, and returns it.
v8::Handle<Value> Item::WrapInstance(iTunesItem* item, char *id) {
  HandleScope scope;

  // If no item was given, then return 'null'
  if (item == nil) {
    return scope.Close(Null());
  }

  // Lookup the 'id' in the ObjectCache
  std::string idStr((const char *)id);

  if (cache.count(idStr) > 0) {
    // if we got in here, then the iTunesItem already has a JS wrapper instance
    // created for it. We should return the same instance.
    v8::Handle<Value> val = cache[idStr];
    return scope.Close(val);
  }

  NSString* className = NSStringFromClass([item class]);
  //NSLog(@"Class: %@", className);
  Local<Object> jsItem;
  if ([className isEqualToString:@"ITunesURLTrack" ]) {
    jsItem = url_track_constructor_template->GetFunction()->NewInstance();
  } else if ([className isEqualToString:@"ITunesFileTrack" ]) {
    jsItem = file_track_constructor_template->GetFunction()->NewInstance();
  } else if ([className isEqualToString:@"ITunesTrack" ]) {
    jsItem = track_constructor_template->GetFunction()->NewInstance();
  } else if ([className isEqualToString:@"ITunesPlaylist" ]) {
    jsItem = playlist_constructor_template->GetFunction()->NewInstance();
  } else if ([className isEqualToString:@"ITunesUserPlaylist" ]) {
    jsItem = user_playlist_constructor_template->GetFunction()->NewInstance();
  } else if ([className isEqualToString:@"ITunesArtwork" ]) {
    jsItem = artwork_constructor_template->GetFunction()->NewInstance();
  } else if ([className isEqualToString:@"ITunesSource" ]) {
    jsItem = source_constructor_template->GetFunction()->NewInstance();
  } else {
    jsItem = item_constructor_template->GetFunction()->NewInstance();
  }
  Item* itemWrap = ObjectWrap::Unwrap<Item>(jsItem);
  itemWrap->itemRef = item;
  // We need to insert this new iTunesItem JS wrapper object into the
  // ObjectCache. If this same iTunesItem is gotten again through another API
  // call, then this same JS object will be returned.
  Persistent<Value> perItem = Persistent<Value>::New(jsItem);
  perItem.MakeWeak((void *)idStr.c_str(), weakItemCacheCallback);
  cache[idStr] = perItem;
  return scope.Close(perItem);
}

}
