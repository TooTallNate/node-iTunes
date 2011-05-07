#include "bindings.h"

using namespace node;
using namespace v8;

namespace node_iTunes {

extern "C" void
init(v8::Handle<Object> target) {
  HandleScope scope;
  node_iTunesApplication::Init(target);
}

} // namespace node_iTunes
