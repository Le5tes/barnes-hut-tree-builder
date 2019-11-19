#include "tree-builder.cpp"
#include <emscripten/bind.h>

using namespace emscripten;

doublePtr_t TreeBuilder::build(doublePtr_t input, int noOfBodies, double width, double cornerX, double cornerY) {
    double *bodies = reinterpret_cast<double*>(input);

    double *result = build(bodies, noOfBodies, width, cornerX, cornerY);
    
    return reinterpret_cast<doublePtr_t>(result);
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("getTreeBuilder", &getTreeBuilder);

    class_<TreeBuilder>("TreeBuilder")
    .constructor<>()
    .function("build", select_overload<doublePtr_t(doublePtr_t, int, double, double, double)>(&TreeBuilder::build), allow_raw_pointers());
}