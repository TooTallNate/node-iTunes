#import <v8.h>
#import <node.h>

#import "Application.h"
#import "Item.h"
#import "iTunes.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

extern "C" void init(v8::Handle<Object> target) {
  HandleScope scope;
  Application::Init(target);
  Item::Init(target);
}

} // namespace node_iTunes
