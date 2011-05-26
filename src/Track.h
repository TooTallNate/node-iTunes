#import <node.h>
#import <v8.h>
#import "Item.h"
#import "iTunes.h"

namespace node_iTunes {

class Track : public Item {
//protected:
//  iTunesTrack* track;

public:
  static v8::Persistent<v8::FunctionTemplate> constructor_template;

  static void Init(v8::Handle<v8::Object>);

  static v8::Handle<v8::Value> New(const v8::Arguments&);

  //static v8::Handle<v8::Value> GetContainerSync(const v8::Arguments&);
  //static v8::Handle<v8::Value> GetIdSync(const v8::Arguments&);
  //static v8::Handle<v8::Value> GetNameSync(const v8::Arguments&);
  //static v8::Handle<v8::Value> GetPersistentIdSync(const v8::Arguments&);

}; // class Track

} // namespace node_iTunes
