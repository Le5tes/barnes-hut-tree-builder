#include "catch.hpp"
#include "../src/tree-builder.cpp"

TEST_CASE("TreeBuilder.build, when called with a single body, should return an array with a single node") {
    TreeBuilder treeBuilder;
    double *bodies = new double[3]{10.0,11.0,100.0};
    
    double *result = treeBuilder.build(bodies, 1, 3000.0, -1500.0, -1500.0);

    REQUIRE(result);

    SECTION("with a reference to the body") {
        REQUIRE(*(result + 7) == 0.0);
    }

    SECTION("with a centre of mass the same as the body") {
        REQUIRE(*result == 10.0);
        REQUIRE(*(result + 1) == 11.0);
        REQUIRE(*(result + 2) == 100.0);
    }

    SECTION("with width the same as passed in") {
        REQUIRE(*(result + 3) == 3000.0);
    }

    SECTION("with corner position the same as passed in") {
        REQUIRE(*(result + 4) == -1500.0);
        REQUIRE(*(result + 5) == -1500.0);
    }

    SECTION("with reference to it's parent node as -1 to indicate that there is no parent") {
        REQUIRE(*(result + 6) == -1.0);
    }

    SECTION("with references to child nodes all as -1 to indicate that there are no child nodes") {
        REQUIRE(*(result + 8) == -1.0);
        REQUIRE(*(result + 9) == -1.0);
        REQUIRE(*(result + 10) == -1.0);
        REQUIRE(*(result + 11) == -1.0);
    }
}
