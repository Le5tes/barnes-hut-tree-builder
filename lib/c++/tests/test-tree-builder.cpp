#include "catch.hpp"
#include "../src/tree-builder.cpp"
#include "../src/body.h"

TEST_CASE("TreeBuilder.build, when called with a single body, should return an array with a single node with reference to that body") {
    TreeBuilder treeBuilder;
    Body *bodies = new Body[1];
    bodies[0].posX = 10.0;
    
    double *result = treeBuilder.build(bodies, 1);

    REQUIRE(result);
    REQUIRE(*result == 10.0);
}
