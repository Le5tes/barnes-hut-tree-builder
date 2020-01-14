#include "../catch.hpp"
#include "../../src/node-array/node-array.h"

TEST_CASE("NodeArray.length- should be 4 times the number of bodies by default") {
    NodeArray nodeArray = NodeArray(3);
    
    REQUIRE(nodeArray.getLength() == 12);
}

TEST_CASE("NodeArray.nextAvailable") {
    NodeArray nodeArray = NodeArray(1);
    
    SECTION("should increment each time it is called to give the next available node in the array") {
        REQUIRE(nodeArray.nextAvailable() == 1);
        REQUIRE(nodeArray.nextAvailable() == 2);
    }
    
    SECTION("when called more times than the array length, should increase the array and otherwise work as normal") {
        REQUIRE(nodeArray.getLength() == 4);
        nodeArray.nextAvailable();
        nodeArray.nextAvailable();
        nodeArray.nextAvailable();
        REQUIRE(nodeArray.nextAvailable() == 4);
        REQUIRE(nodeArray.getLength() == 8);
        // Sadly it seems this will often pass without being implemented properly!
        REQUIRE_NOTHROW(nodeArray.mass(4));
    }
}