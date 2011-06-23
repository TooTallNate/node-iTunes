#import <v8.h>

namespace node_iTunes {

  // All the JavaScript Class constructor functions need to be defined here.
  // This is to avoid circular dependencies with header files and specifically
  // the "Item::WrapInstance" function, which intelligently uses the proper JS
  // constuctor based on the given iTunesItem instance.
  extern v8::Persistent<v8::FunctionTemplate> application_constructor_template;
  extern v8::Persistent<v8::FunctionTemplate> item_constructor_template;
  extern v8::Persistent<v8::FunctionTemplate> track_constructor_template;
  extern v8::Persistent<v8::FunctionTemplate> file_track_constructor_template;
  extern v8::Persistent<v8::FunctionTemplate> url_track_constructor_template;
  extern v8::Persistent<v8::FunctionTemplate> playlist_constructor_template;
  extern v8::Persistent<v8::FunctionTemplate> user_playlist_constructor_template;
  extern v8::Persistent<v8::FunctionTemplate> source_constructor_template;

} // namespace node_iTunes
