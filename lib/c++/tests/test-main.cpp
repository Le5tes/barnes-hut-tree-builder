#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/tree/tree.cpp"
#include "test-tree-builder.cpp"
#include "body-array/test-body-array.cpp"
#include "node-array/test-node-array.cpp"

TEST_CASE("test test!") {
    REQUIRE(1 == 1);
}