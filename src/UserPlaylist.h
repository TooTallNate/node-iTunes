#import <node.h>
#import <v8.h>
#import "js_constructors.h"
#import "Playlist.h"
#import "iTunes.h"

namespace node_iTunes {

class UserPlaylist : public Playlist {
public:
  static void Init(v8::Handle<v8::Object>);

  static v8::Handle<v8::Value> New(const v8::Arguments&);

  static v8::Handle<v8::Value> FileTracks(const v8::Arguments&);
  static v8::Handle<v8::Value> URLTracks(const v8::Arguments&);
  static v8::Handle<v8::Value> SharedTracks(const v8::Arguments&);

  static v8::Handle<v8::Value> Shared(const v8::Arguments&);
  static v8::Handle<v8::Value> Smart(const v8::Arguments&);

}; // class UserPlaylist

} // namespace node_iTunes
