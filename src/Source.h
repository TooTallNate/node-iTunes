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

  static v8::Handle<v8::Value> GetAudioCDPlaylists(const v8::Arguments&);
  static v8::Handle<v8::Value> GetDevicePlaylists(const v8::Arguments&);
  static v8::Handle<v8::Value> GetLibraryPlaylists(const v8::Arguments&);
  static v8::Handle<v8::Value> GetPlaylists(const v8::Arguments&);
  static v8::Handle<v8::Value> GetRadioTunerPlaylists(const v8::Arguments&);
  static v8::Handle<v8::Value> GetUserPlaylists(const v8::Arguments&);

  static v8::Handle<v8::Value> GetCapacity(const v8::Arguments&);
  static v8::Handle<v8::Value> GetFreeSpace(const v8::Arguments&);
  static v8::Handle<v8::Value> GetKind(const v8::Arguments&);

}; // class Source

} // namespace node_iTunes
