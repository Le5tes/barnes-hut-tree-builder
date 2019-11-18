#include "catch.hpp"
#include "../src/tree-builder.cpp"

TEST_CASE("TreeBuilder.build, when called with a single body, should return an array with a single node with reference to that body") {
    TreeBuilder treeBuilder;
    double *bodies = new double[3]{10.0,11.0,100.0};
    
    double *result = treeBuilder.build(bodies, 1);

    REQUIRE(result);
    REQUIRE(*result == 10.0);
    REQUIRE(*(result + 1) == 11.0);
    REQUIRE(*(result + 2) == 100.0);
}
