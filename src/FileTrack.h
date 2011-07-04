#import <node.h>
#import <v8.h>
#import "js_constructors.h"
#import "Track.h"
#import "iTunes.h"

namespace node_iTunes {

class FileTrack : public Track {
public:
  static void Init(v8::Handle<v8::Object>);

  static v8::Handle<v8::Value> New(const v8::Arguments&);

  static v8::Handle<v8::Value> Location(const v8::Arguments&);

  static v8::Handle<v8::Value> Refresh(const v8::Arguments&);

private:
  static int EIO_Location (eio_req *req);
  static int EIO_AfterLocation (eio_req *req);

}; // class FileTrack

} // namespace node_iTunes
