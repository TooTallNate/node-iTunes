#import <v8.h>
#import <node.h>

#import "Application.h"
#import "Artwork.h"
#import "Item.h"
#import "Track.h"
#import "FileTrack.h"
#import "URLTrack.h"
#import "Playlist.h"
#import "Source.h"
#import "UserPlaylist.h"
#import "iTunes.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

v8::Persistent<v8::FunctionTemplate> application_constructor_template;
v8::Persistent<v8::FunctionTemplate> artwork_constructor_template;
v8::Persistent<v8::FunctionTemplate> item_constructor_template;
v8::Persistent<v8::FunctionTemplate> track_constructor_template;
v8::Persistent<v8::FunctionTemplate> file_track_constructor_template;
v8::Persistent<v8::FunctionTemplate> url_track_constructor_template;
v8::Persistent<v8::FunctionTemplate> playlist_constructor_template;
v8::Persistent<v8::FunctionTemplate> source_constructor_template;
v8::Persistent<v8::FunctionTemplate> user_playlist_constructor_template;

extern "C" void init(v8::Handle<Object> target) {
  HandleScope scope;
  Application::Init(target);
  Item::Init(target);
  Artwork::Init(target);
  Track::Init(target);
  FileTrack::Init(target);
  URLTrack::Init(target);
  Playlist::Init(target);
  UserPlaylist::Init(target);
  Source::Init(target);
}

} // namespace node_iTunes
