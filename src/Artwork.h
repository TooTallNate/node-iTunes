#import <node.h>
#import <v8.h>
#import "js_constructors.h"
#import "Item.h"
#import "iTunes.h"

namespace node_iTunes {

class Artwork : public Item {
public:
  static void Init(v8::Handle<v8::Object>);

  static v8::Handle<v8::Value> New(const v8::Arguments&);

  static v8::Handle<v8::Value> Data(const v8::Arguments&);
  static v8::Handle<v8::Value> Downloaded(const v8::Arguments&);
  static v8::Handle<v8::Value> Format(const v8::Arguments&);
  static v8::Handle<v8::Value> Kind(const v8::Arguments&);

private:
  static int EIO_Data(eio_req *);
  static int EIO_AfterData(eio_req *);

}; // class Artwork

} // namespace node_iTunes
