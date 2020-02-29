#include "../../src/node-array/node-array.h"
#include "../utils/testing-node-array.h"
#include "../../src/body-array/body-array.h"
#include "../../src/tree/tree.cpp"

TEST_CASE("#setupNode should setup a new node at the index provided, with parent node, corners and width provided") {
    double *bodies = new double[3]{10.0,11.0,100.0};
    BodyArray bodyArray {bodies};
    Tree tree {1, bodyArray};
    
    tree.setupNode(0, 2, 100.0, -50.0, -50.0);
    
    TestingNodeArray nodes {tree.getNodes(), 1};
    
    REQUIRE(nodes.mass(0)  == 0.0);
    REQUIRE(nodes.width(0) == 100.0);
    REQUIRE(nodes.cornerX(0) == -50.0);
    REQUIRE(nodes.cornerY(0) == -50.0);
    REQUIRE(nodes.parentAddr(0) == 2.0);
    REQUIRE(nodes.bodyAddr(0) == -1.0);
    REQUIRE(nodes.subnode1Addr(0) == -1.0);
    REQUIRE(nodes.subnode2Addr(0) == -1.0);
    REQUIRE(nodes.subnode3Addr(0) == -1.0);
    REQUIRE(nodes.subnode4Addr(0) == -1.0);
}

TEST_CASE("#addBody should add a body from the bodies array to the tree") {
    SECTION("when called with an empty node index, where the node no body or subnodes") {
        double *bodies = new double[3]{10.0,11.0,100.0};
        BodyArray bodyArray {bodies};
        Tree tree {1, bodyArray};
        tree.setupNode(0, -1, 100.0, -50.0, -50.0);

        tree.addBody(0, 0);
        TestingNodeArray nodes {tree.getNodes(), 1};

        SECTION("it should set the body address to the node's bodyAddress") {
            REQUIRE(nodes.bodyAddr(0) == 0.0);
        }
        
        SECTION("it should set the node's centre of mass to match the body's") {
            REQUIRE(nodes.mass(0) == 100.0);
            REQUIRE(nodes.posX(0) == 10.0);
            REQUIRE(nodes.posY(0) == 11.0);
        }
    }
    
    SECTION("when called with a node index where the node already has a body") {
        double *bodies = new double[6]{10.0,11.0,100.0, -5.0, 7.0, 150.0};
        BodyArray bodyArray {bodies};
        Tree tree {2, bodyArray};
        tree.setupNode(0, -1, 100.0, -50.0, -50.0);

        tree.addBody(0, 0);
        tree.addBody(0, 1);

        TestingNodeArray nodes {tree.getNodes(), 3};
        
        SECTION("it should create two new subnodes") {
            SECTION("with the original node as the parent") {
                REQUIRE(nodes.parentAddr(1) == 0);
                REQUIRE(nodes.parentAddr(2) == 0);
            }
            
            SECTION("with the two bodies added to the subnodes") {
                REQUIRE(nodes.bodyAddr(1) == 0);
                REQUIRE(nodes.bodyAddr(2) == 1);
            }
        }
        
        SECTION("the original body") {
            SECTION("should no longer have a reference to the first body") {
                REQUIRE(nodes.bodyAddr(0) == -1);
            }

            SECTION("should have the centre of mass worked out for both subnodes") {
                REQUIRE(nodes.mass(0) == 250.0);
                REQUIRE(nodes.posX(0) == 1.0);
                REQUIRE(nodes.posY(0) == 8.6);
            }
        }
    }
    
    // TODO
    SECTION("when called with a node index that does not exist") {}
    
    // TODO
    SECTION("when called with a body index that does not exist") {}
}
