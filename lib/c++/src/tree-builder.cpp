#include "tree-builder.h"
#include <emscripten/bind.h>
using namespace emscripten;

TreeBuilder getTreeBuilder() {
    TreeBuilder treeBuilder;
    return treeBuilder;
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("getTreeBuilder", &getTreeBuilder);

    class_<TreeBuilder>("TreeBuilder")
    .constructor<>()
    .function("build", &TreeBuilder::build, allow_raw_pointers());
}