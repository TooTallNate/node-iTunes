#import <node.h>
#import <v8.h>
#import "iTunes.h"

namespace node_iTunes {

class Item : public node::ObjectWrap {
protected:
  iTunesItem* item;

public:
  static v8::Persistent<v8::FunctionTemplate> constructor_template;

  Item();
  ~Item();

  static void Init(v8::Handle<v8::Object>);

  static v8::Handle<v8::Value> New(const v8::Arguments&);

  static v8::Handle<v8::Value> GetContainerSync(const v8::Arguments&);
  static v8::Handle<v8::Value> GetIdSync(const v8::Arguments&);
  static v8::Handle<v8::Value> GetNameSync(const v8::Arguments&);
  static v8::Handle<v8::Value> GetPersistentIdSync(const v8::Arguments&);

}; // class Item

} // namespace node_iTunes
