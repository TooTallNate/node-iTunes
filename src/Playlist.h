#import <node.h>
#import <v8.h>
#import "js_constructors.h"
#import "Item.h"
#import "iTunes.h"

namespace node_iTunes {

class Playlist : public Item {
public:
  static void Init(v8::Handle<v8::Object>);

  static v8::Handle<v8::Value> New(const v8::Arguments&);

  static v8::Handle<v8::Value> GetTracks(const v8::Arguments&);

  static v8::Handle<v8::Value> GetDuration(const v8::Arguments&);
  static v8::Handle<v8::Value> GetIndex(const v8::Arguments&);
  static v8::Handle<v8::Value> GetParent(const v8::Arguments&);
  static v8::Handle<v8::Value> IsShuffled(const v8::Arguments&);
  static v8::Handle<v8::Value> GetSize(const v8::Arguments&);
  static v8::Handle<v8::Value> GetRepeat(const v8::Arguments&);
  static v8::Handle<v8::Value> GetSpecialKind(const v8::Arguments&);
  static v8::Handle<v8::Value> GetTime(const v8::Arguments&);
  static v8::Handle<v8::Value> IsVisible(const v8::Arguments&);

}; // class Playlist

} // namespace node_iTunes
