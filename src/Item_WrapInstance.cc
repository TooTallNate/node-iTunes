#include "Item.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

// Convenience function that takes an iTunesItem instance (or any subclass)
// and wraps it up into the proper JS class type, and returns it.
// TODO: Implement some kind of Object Cache, so if the same instance is
//       attempting to be wrapped again, then the same JS Object is returned.
v8::Handle<Value> Item::WrapInstance(iTunesItem* item) {
  HandleScope scope;

  //NSLog(@"%@", [item persistentID]);
  if (item == nil) {
    return scope.Close(Null());
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
  } else if ([className isEqualToString:@"ITunesSource" ]) {
    jsItem = source_constructor_template->GetFunction()->NewInstance();
  } else {
    jsItem = item_constructor_template->GetFunction()->NewInstance();
  }
  Item* itemWrap = ObjectWrap::Unwrap<Item>(jsItem);
  itemWrap->itemRef = item;
  return scope.Close(jsItem);
}

}
