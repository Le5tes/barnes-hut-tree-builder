#include "catch.hpp"
#include "../src/tree-builder.h"

TEST_CASE("TreeBuilder.build should return a pointer to an array") {
    TreeBuilder treeBuilder;
    double *arr = treeBuilder.build();
    double exp[] = {3.0};
    REQUIRE(arr[0] == exp[0]);
}

TEST_CASE("TreeBuilder.build should throw an error if the pointer is already assigned") {
    
}
