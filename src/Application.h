#import <node.h>
#import <v8.h>
#import "js_constructors.h"
#import "Track.h"
#import "iTunes.h"

namespace node_iTunes {

struct create_connection_request {
  char* host;
  char* username;
  char* password;
  v8::Persistent<v8::Function> cb;
  iTunesApplication* iTunesRef;
};

int CreateConnection_Do (eio_req *req);
int CreateConnection_After (eio_req *req);

class Application : public node::ObjectWrap {
public:
  iTunesApplication* iTunesRef;

  Application();
  ~Application();

  static void Init(v8::Handle<v8::Object>);

  // JS Constructor
  static v8::Handle<v8::Value> New(const v8::Arguments&);

  // The proper way to get an Application instance in JS-land
  static v8::Handle<v8::Value> CreateConnection(const v8::Arguments&);

  // iTunes Functions -> JS Functions
  static v8::Handle<v8::Value> QuitSync(const v8::Arguments&);
  //static v8::Handle<v8::Value> RunSync(const v8::Arguments&);
  static v8::Handle<v8::Value> IsRunningSync(const v8::Arguments&);
  /*static v8::Handle<v8::Value> AddSync(const v8::Arguments&);
  static v8::Handle<v8::Value> BackTrackSync(const v8::Arguments&);
  static v8::Handle<v8::Value> ConvertSync(const v8::Arguments&);
  static v8::Handle<v8::Value> FastForwardSync(const v8::Arguments&);
  static v8::Handle<v8::Value> NextTrackSync(const v8::Arguments&);
  static v8::Handle<v8::Value> PauseSync(const v8::Arguments&);
  static v8::Handle<v8::Value> PlayOnceSync(const v8::Arguments&);
  static v8::Handle<v8::Value> PlayPauseSync(const v8::Arguments&);
  static v8::Handle<v8::Value> PreviousTrackSync(const v8::Arguments&);
  static v8::Handle<v8::Value> ResumeSync(const v8::Arguments&);
  static v8::Handle<v8::Value> RewindSync(const v8::Arguments&);
  static v8::Handle<v8::Value> StopSync(const v8::Arguments&);
  static v8::Handle<v8::Value> UpdateSync(const v8::Arguments&);
  static v8::Handle<v8::Value> EjectSync(const v8::Arguments&);
  static v8::Handle<v8::Value> SubscribeSync(const v8::Arguments&);
  static v8::Handle<v8::Value> UpdateAllPodcastsSync(const v8::Arguments&);
  static v8::Handle<v8::Value> UpdatePodcastSync(const v8::Arguments&);
  static v8::Handle<v8::Value> OpenLocationSync(const v8::Arguments&);*/

  // iTunes Property Getters -> JS Functions
  static v8::Handle<v8::Value> GetCurrentTrackSync(const v8::Arguments&);
  static v8::Handle<v8::Value> GetSelectionSync(const v8::Arguments&);
  static v8::Handle<v8::Value> GetVolumeSync(const v8::Arguments&);

  // iTunes Property Setters -> JS Functions
  static v8::Handle<v8::Value> SetVolumeSync(const v8::Arguments&);

}; // class iTunesApplication

} // namespace node_iTunes
