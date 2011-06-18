#import <node.h>
#import <v8.h>
#import "js_constructors.h"
#import "Track.h"
#import "iTunes.h"

namespace node_iTunes {

class URLTrack : public Track {
public:
  static void Init(v8::Handle<v8::Object>);

  static v8::Handle<v8::Value> New(const v8::Arguments&);

  //static v8::Handle<v8::Value> GetContainer(const v8::Arguments&);
  //static v8::Handle<v8::Value> GetId(const v8::Arguments&);
  //static v8::Handle<v8::Value> GetName(const v8::Arguments&);
  //static v8::Handle<v8::Value> GetPersistentId(const v8::Arguments&);

}; // class Track

} // namespace node_iTunes
