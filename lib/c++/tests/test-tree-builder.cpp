#include "catch.hpp"
#include "../src/tree-builder.cpp"
#include "utils/testing-node-array.h"

TEST_CASE("TreeBuilder.build, when called with a single body, should return an array with a single node") {
    TreeBuilder treeBuilder;
    double *bodies = new double[3]{10.0,11.0,100.0};
    
    TestingNodeArray result {treeBuilder.build(bodies, 1, 3000.0, -1500.0, -1500.0), 1};

    SECTION("with a reference to the body") {
        REQUIRE(result.bodyAddr(0) == 0);
    }

    SECTION("with a centre of mass the same as the body") {
        REQUIRE(result.posX(0) == 10.0);
        REQUIRE(result.posY(0) == 11.0);
        REQUIRE(result.mass(0) == 100.0);
    }

    SECTION("with width the same as passed in") {
        REQUIRE(result.width(0) == 3000.0);
    }

    SECTION("with corner position the same as passed in") {
        REQUIRE(result.cornerX(0) == -1500.0);
        REQUIRE(result.cornerY(0) == -1500.0);
    }

    SECTION("with reference to it's parent node as -1 to indicate that there is no parent") {
        REQUIRE(result.parentAddr(0) == -1);
    }

    SECTION("with references to child nodes all as -1 to indicate that there are no child nodes") {
        REQUIRE(result.subnode1Addr(0) == -1);
        REQUIRE(result.subnode2Addr(0) == -1);
        REQUIRE(result.subnode3Addr(0) == -1);
        REQUIRE(result.subnode4Addr(0) == -1);
    }
}

TEST_CASE("TreeBuilder.build, when called with two bodies, should return an array with three nodes") {
    TreeBuilder treeBuilder;

    double *bodies = new double[6]{10.0, 11.0, 100.0, -10.0, 25.0, 100.0};
    TestingNodeArray result {treeBuilder.build(bodies, 2, 3000.0, -1500.0, -1500.0), 3};
    
    SECTION("Parent node"){
        SECTION("Has no parent") {
            REQUIRE(result.parentAddr(0) == -1);
        }
        
        SECTION("Has 2 children") {
            REQUIRE(result.subnode1Addr(0) == -1);
            REQUIRE(result.subnode2Addr(0) == -1);
            REQUIRE(result.subnode3Addr(0) == 2);
            REQUIRE(result.subnode4Addr(0) == 1);
        } 
    
        SECTION("has no body attached to it") {
            REQUIRE(result.bodyAddr(0) == -1);
        }
    
        SECTION("has width the same as passed in") {
            REQUIRE(result.width(0) == 3000.0);
        }
    
        SECTION("has corner position the same as passed in") {
            REQUIRE(result.cornerX(0) == -1500.0);
            REQUIRE(result.cornerY(0) == -1500.0);
        }
    
        SECTION("has centre of mass created by amalgamating the two bodies") {
            REQUIRE(result.posX(0) == 0.0);
            REQUIRE(result.posY(0) == 18.0);
            REQUIRE(result.mass(0) == 200.0);
        }
    }
    
    SECTION("child nodes") {
        SECTION("third child should have the second body") {
            REQUIRE(result.bodyAddr(2) == 1);
        }
        
        SECTION("fourth child should have the first body") {
            REQUIRE(result.bodyAddr(1) == 0);
        }
    }
}

TEST_CASE("TreeBuilder.build, when called with two bodies with the same position should handle gracefully!") {
    TreeBuilder treeBuilder;
    
    double *bodies = new double[6]{10.0, 11.0, 100.0, 10.0, 11.0, 101.0};

    REQUIRE_NOTHROW(treeBuilder.build(bodies, 2, 3000.0, -1500.0, -1500.0));
}

TEST_CASE("TreeBuilder.build, when it overruns the array, should not throw errors") {
    TreeBuilder treeBuilder;

    double *bodies = new double[6]{10.0, 11.1, 100.0, 10.0, 11.0, 101.0};

    REQUIRE_NOTHROW(treeBuilder.build(bodies, 2, 3000.0, -1500.0, -1500.0));
}

TEST_CASE("TreeBuilder.length, should return the length of the nodeArray") {
    TreeBuilder treeBuilder;
    
    SECTION("when tree is not yet initialised - should return 0") {
        REQUIRE(treeBuilder.getTreeLength() == 0);
    }
    
    SECTION("after build - no array extension") {
        double *bodies = new double[3]{10.0, 11.1, 100.0};

        treeBuilder.build(bodies, 1, 3000.0, -1500.0, -1500.0);

        REQUIRE(treeBuilder.getTreeLength() == 4);
    }
    
    SECTION("after build - with array extension") {
        double *bodies = new double[6]{10.0, 11.1, 100.0, 10.0, 11.0, 101.0};

        treeBuilder.build(bodies, 2, 3000.0, -1500.0, -1500.0);

        REQUIRE(treeBuilder.getTreeLength() == 32);
    }
}

TEST_CASE("TreeBuilder.build, when called multiple times should overwrite the array rather than extending it") {
    TreeBuilder treeBuilder;
    double *bodies = new double[6]{10.0, 11.0, 100.0, -10.0, 25.0, 100.0};
    
    treeBuilder.build(bodies, 2, 3000.0, -1500.0, -1500.0);
    treeBuilder.build(bodies, 2, 3000.0, -1500.0, -1500.0);
    
    REQUIRE(treeBuilder.getTreeLength() == 8);
}

TEST_CASE("TreeBuilder.build, when called with a body outside of the bounds, should not include it in the tree") {
    TreeBuilder treeBuilder;
    double *bodies = new double[6]{10.0,11.0,100.0,10.0,155.0,100.0};

    TestingNodeArray result {treeBuilder.build(bodies, 2, 300.0, -150.0, -150.0), 1};

    REQUIRE(result.posX(0) == 10.0);
    REQUIRE(result.posY(0) == 11.0);
    REQUIRE(result.mass(0) == 100.0);
    REQUIRE(result.bodyAddr(0) == 0);
    REQUIRE(result.subnode1Addr(0) == -1);
    REQUIRE(result.subnode2Addr(0) == -1);
    REQUIRE(result.subnode3Addr(0) == -1);
    REQUIRE(result.subnode4Addr(0) == -1);
}

TEST_CASE("TreeBuilder.build, when called with two body outside of the bounds, should not throw errors") {
    TreeBuilder treeBuilder;
    double *bodies = new double[9]{10.0,11.0,100.0,10.0,155.0,100.0,10.0,156.0,100.0};

    REQUIRE_NOTHROW(treeBuilder.build(bodies, 3, 300.0, -150.0, -150.0));
}
