#import <pthread.h>
#import <node.h>
#import <v8.h>
#import "js_constructors.h"
#import "Track.h"
#import "iTunes.h"

namespace node_iTunes {

// A note on ScriptingBridge "Thread Safety": Essentially any SBObject needs to
// only have one thread accessing it at a time. A pthread mutex lock will be
// required to ensure that only one EIO thread access any given item at a time:
//   http://developer.apple.com/library/mac/releasenotes/ScriptingAutomation/RN-ScriptingBridge

class Application : public node::ObjectWrap {
public:
  iTunesApplication* itemRef;

  Application();
  ~Application();

  static void Init(v8::Handle<v8::Object>);

  // JS Constructor
  static v8::Handle<v8::Value> New(const v8::Arguments&);

  // The proper way to get an Application instance in JS-land
  static v8::Handle<v8::Value> CreateConnection(const v8::Arguments&);

  // iTunes Functions -> JS Functions
  static v8::Handle<v8::Value> Quit(const v8::Arguments&);
  static v8::Handle<v8::Value> Run(const v8::Arguments&);
  static v8::Handle<v8::Value> Running(const v8::Arguments&);
  static v8::Handle<v8::Value> Add(const v8::Arguments&);
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
  static v8::Handle<v8::Value> OpenLocation(const v8::Arguments&);

  // Children ElementArrays
  static v8::Handle<v8::Value> BrowserWindows(const v8::Arguments&);
  static v8::Handle<v8::Value> Encoders(const v8::Arguments&);
  static v8::Handle<v8::Value> EQPresets(const v8::Arguments&);
  static v8::Handle<v8::Value> EQWindows(const v8::Arguments&);
  static v8::Handle<v8::Value> PlaylistWindows(const v8::Arguments&);
  static v8::Handle<v8::Value> Sources(const v8::Arguments&);
  static v8::Handle<v8::Value> Visuals(const v8::Arguments&);
  static v8::Handle<v8::Value> Windows(const v8::Arguments&);

  // iTunes Property -> JS Functions
  static v8::Handle<v8::Value> CurrentTrack(const v8::Arguments&);
  static v8::Handle<v8::Value> Selection(const v8::Arguments&);
  static v8::Handle<v8::Value> Volume(const v8::Arguments&);

  // 'toString()' override
  static v8::Handle<v8::Value> ToString(const v8::Arguments&);

protected:
  pthread_mutex_t mutex;

private:
  static int EIO_CreateConnection (eio_req *);
  static int EIO_AfterCreateConnection (eio_req *);

  static int EIO_Sources (eio_req *);
  static int EIO_AfterSources (eio_req *);

  static int EIO_CurrentTrack (eio_req *);
  static int EIO_AfterCurrentTrack (eio_req *);

  static int EIO_Selection (eio_req *);
  static int EIO_AfterSelection (eio_req *);

  static int EIO_Volume (eio_req *);
  static int EIO_AfterVolume (eio_req *);

}; // class iTunesApplication

} // namespace node_iTunes
