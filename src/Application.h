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
  static v8::Handle<v8::Value> Quit(const v8::Arguments&);
  //static v8::Handle<v8::Value> Run(const v8::Arguments&);
  static v8::Handle<v8::Value> IsRunning(const v8::Arguments&);
  /*static v8::Handle<v8::Value> Add(const v8::Arguments&);
  static v8::Handle<v8::Value> BackTrack(const v8::Arguments&);
  static v8::Handle<v8::Value> Convert(const v8::Arguments&);
  static v8::Handle<v8::Value> FastForward(const v8::Arguments&);
  static v8::Handle<v8::Value> NextTrack(const v8::Arguments&);
  static v8::Handle<v8::Value> Pause(const v8::Arguments&);
  static v8::Handle<v8::Value> PlayOnce(const v8::Arguments&);
  static v8::Handle<v8::Value> PlayPause(const v8::Arguments&);
  static v8::Handle<v8::Value> PreviousTrack(const v8::Arguments&);
  static v8::Handle<v8::Value> Resume(const v8::Arguments&);
  static v8::Handle<v8::Value> Rewind(const v8::Arguments&);
  static v8::Handle<v8::Value> Stop(const v8::Arguments&);
  static v8::Handle<v8::Value> Update(const v8::Arguments&);
  static v8::Handle<v8::Value> Eject(const v8::Arguments&);
  static v8::Handle<v8::Value> Subscribe(const v8::Arguments&);
  static v8::Handle<v8::Value> UpdateAllPodcasts(const v8::Arguments&);
  static v8::Handle<v8::Value> UpdatePodcast(const v8::Arguments&);
  static v8::Handle<v8::Value> OpenLocation(const v8::Arguments&);*/

  // iTunes Property Getters -> JS Functions
  static v8::Handle<v8::Value> GetCurrentTrack(const v8::Arguments&);
  static v8::Handle<v8::Value> GetSelection(const v8::Arguments&);
  static v8::Handle<v8::Value> GetVolume(const v8::Arguments&);

  // iTunes Property Setters -> JS Functions
  static v8::Handle<v8::Value> SetVolume(const v8::Arguments&);

}; // class iTunesApplication

} // namespace node_iTunes
