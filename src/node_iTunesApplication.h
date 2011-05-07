#ifndef NIT_ITUNESAPPLICATION_H
#define NIT_ITUNESAPPLICATION_H

#include <node.h>
#include <v8.h>
#import "iTunes.h"

namespace node_iTunes {

class node_iTunesApplication : public node::ObjectWrap {
private:
  iTunesApplication* iTunesRef;

public:
  static v8::Persistent<v8::FunctionTemplate> constructor_template;

  node_iTunesApplication();
  ~node_iTunesApplication();
  static void Init(v8::Handle<v8::Object>);
  static v8::Handle<v8::Value> New(const v8::Arguments&);
  static v8::Handle<v8::Value> GetVolumeSync(const v8::Arguments&);

}; // class node_iTunesApplication

} // namespace node_iTunes

#endif // NIT_ITUNESAPPLICATION_H
