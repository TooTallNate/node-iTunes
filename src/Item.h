#import <node.h>
#import <v8.h>
#import "js_constructors.h"
#import "iTunes.h"

namespace node_iTunes {

class Item : public node::ObjectWrap {
public:

  // The reference that this JS instance is representing
  iTunesItem* itemRef;

  Item();
  ~Item();

  static void Init(v8::Handle<v8::Object>);

  static v8::Handle<v8::Value> New(const v8::Arguments&);

  // iTunes Property Getters -> JS Functions
  static v8::Handle<v8::Value> GetContainerSync(const v8::Arguments&);
  static v8::Handle<v8::Value> GetIdSync(const v8::Arguments&);
  static v8::Handle<v8::Value> GetNameSync(const v8::Arguments&);
  static v8::Handle<v8::Value> GetPersistentIdSync(const v8::Arguments&);

  // iTunes Property Setters -> JS Functions
  static v8::Handle<v8::Value> SetNameSync(const v8::Arguments&);

}; // class Item

} // namespace node_iTunes
