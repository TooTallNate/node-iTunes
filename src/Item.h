#include <pthread.h>
#import <node.h>
#import <v8.h>
#import "js_constructors.h"
#import "iTunes.h"

namespace node_iTunes {

/**
 * Item
 * ====
 *
 * Base class for all iTunes classes (except for Application)
 */
class Item : public node::ObjectWrap {
public:

  // The reference that this JS instance is representing.
  // It's public so that subclasses can set this property when they're created
  iTunesItem* itemRef;

  Item();
  ~Item();

  static void Init(v8::Handle<v8::Object>);

  static v8::Handle<v8::Value> WrapInstance(iTunesItem* track, const char *id);
  static v8::Handle<v8::Value> New(const v8::Arguments&);

  // iTunes Property -> JS Functions
  static v8::Handle<v8::Value> Container(const v8::Arguments&);
  static v8::Handle<v8::Value> Id(const v8::Arguments&);
  static v8::Handle<v8::Value> Name(const v8::Arguments&);
  static v8::Handle<v8::Value> PersistentId(const v8::Arguments&);

  // 'toString()' override
  static v8::Handle<v8::Value> ToString(const v8::Arguments&);

protected:
  pthread_mutex_t mutex;

private:
  static int EIO_Name (eio_req *);
  static int EIO_AfterName (eio_req *);

  static int EIO_Id (eio_req *);
  static int EIO_AfterId (eio_req *);

  static int EIO_PersistentId (eio_req *);
  static int EIO_AfterPersistentId (eio_req *);

  static int EIO_Container (eio_req *);
  static int EIO_AfterContainer (eio_req *);

}; // class Item

} // namespace node_iTunes
