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

TEST_CASE("TreeBuilder.build, when called with two bodies, should return an array with five nodes") {
    TreeBuilder treeBuilder;

    double *bodies = new double[6]{10.0,11.0,100.0, -10.0,25.0,100.0};
    double *result = treeBuilder.build(bodies, 2, 3000.0, -1500.0, -1500.0);
    
    SECTION("Parent node"){
        SECTION("Has no parent") {
            REQUIRE(*(result + 6) == -1.0);
        }
        
        SECTION("Has 4 children") {
            REQUIRE(*(result + 8) == 1.0);
            REQUIRE(*(result + 9) == 2.0);
            REQUIRE(*(result + 10) == 3.0);
            REQUIRE(*(result + 11) == 4.0);
        } 
    
        SECTION("has no body attached to it") {
            REQUIRE(*(result + 7) == -1.0);
        }
    
        SECTION("has width the same as passed in") {
            REQUIRE(*(result + 3) == 3000.0);
        }
    
        SECTION("has corner position the same as passed in") {
            REQUIRE(*(result + 4) == -1500.0);
            REQUIRE(*(result + 5) == -1500.0);
        }
    
        SECTION("has centre of mass created by amalgamating the two bodies") {
            REQUIRE(*result == 0.0);
            REQUIRE(*(result + 1) == 18.0);
            REQUIRE(*(result + 2) == 200.0);
        }
    }
    
    SECTION("child nodes") {
        SECTION("first child should have no body") {
            REQUIRE(*(result+19) == -1.0);
        }
        
        SECTION("second child should have no body") {
            REQUIRE(*(result+31) == -1.0);
        }
        
        SECTION("third child should have the second body") {
            REQUIRE(*(result+43) == 1.0);
        }
        
        SECTION("fourth child should have the first body") {
            REQUIRE(*(result+55) == 0.0);
        }
    }
}