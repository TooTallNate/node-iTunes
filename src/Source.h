#import <node.h>
#import <v8.h>
#import "js_constructors.h"
#import "Item.h"
#import "iTunes.h"

namespace node_iTunes {

class Source : public Item {
public:
  static void Init(v8::Handle<v8::Object>);

  static v8::Handle<v8::Value> New(const v8::Arguments&);

  static v8::Handle<v8::Value> Update(const v8::Arguments&);
  static v8::Handle<v8::Value> Eject(const v8::Arguments&);

  static v8::Handle<v8::Value> AudioCDPlaylists(const v8::Arguments&);
  static v8::Handle<v8::Value> DevicePlaylists(const v8::Arguments&);
  static v8::Handle<v8::Value> LibraryPlaylists(const v8::Arguments&);
  static v8::Handle<v8::Value> Playlists(const v8::Arguments&);
  static v8::Handle<v8::Value> RadioTunerPlaylists(const v8::Arguments&);
  static v8::Handle<v8::Value> UserPlaylists(const v8::Arguments&);

  static v8::Handle<v8::Value> Capacity(const v8::Arguments&);
  static v8::Handle<v8::Value> FreeSpace(const v8::Arguments&);
  static v8::Handle<v8::Value> Kind(const v8::Arguments&);

private:
  static int EIO_Playlists (eio_req *);
  static int EIO_AfterPlaylists (eio_req *);

  static int EIO_Kind (eio_req *);
  static int EIO_AfterKind (eio_req *);

}; // class Source

} // namespace node_iTunes
