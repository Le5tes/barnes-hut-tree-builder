#include "catch.hpp"
#include "../src/tree-builder.h"

TEST_CASE("TreeBuilder.build, when called with a single body, should return an array with a single node with reference to that body") {
    TreeBuilder treeBuilder;
    double (*bodies)[5] =  new double[1][5]{{10.0,10.0,100.0,0.0,0.0}};
    
    double *result = treeBuilder.build(bodies);

    REQUIRE(result);
    REQUIRE(*result == 10.0);
}
