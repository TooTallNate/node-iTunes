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

  static v8::Handle<v8::Value> WrapInstance(iTunesItem* track, char *id);
  static v8::Handle<v8::Value> New(const v8::Arguments&);

  // iTunes Property Getters -> JS Functions
  static v8::Handle<v8::Value> GetContainer(const v8::Arguments&);
  static v8::Handle<v8::Value> GetId(const v8::Arguments&);
  static v8::Handle<v8::Value> GetName(const v8::Arguments&);
  static v8::Handle<v8::Value> GetPersistentId(const v8::Arguments&);

  // iTunes Property Setters -> JS Functions
  static v8::Handle<v8::Value> SetName(const v8::Arguments&);

private:
  static int EIO_GetName (eio_req *);
  static int EIO_AfterGetName (eio_req *);

  static int EIO_GetId (eio_req *);
  static int EIO_AfterGetId (eio_req *);

  static int EIO_GetPersistentId (eio_req *);
  static int EIO_AfterGetPersistentId (eio_req *);

  static int EIO_GetContainer (eio_req *);
  static int EIO_AfterGetContainer (eio_req *);

  static int EIO_SetName (eio_req *);
  static int EIO_AfterSetName (eio_req *);

}; // class Item

} // namespace node_iTunes
