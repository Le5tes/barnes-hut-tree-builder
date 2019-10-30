#include "tree-builder.cpp"
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(my_module) {
    function("getTreeBuilder", &getTreeBuilder);
    
    value_object<Body>("Body")
    .field("mass", &Body::mass)
    .field("posX", &Body::posX)
    .field("posY", &Body::posY);

    class_<TreeBuilder>("TreeBuilder")
    .constructor<>()
    .function("build", &TreeBuilder::build, allow_raw_pointers());
}