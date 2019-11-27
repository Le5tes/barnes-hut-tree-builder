#include "catch.hpp"
#include "../src/body-array.h"

TEST_CASE("should receive an array and allow the retreival of values") {
    double *bodies = new double[9] {5.0, 145.7, 10.0, -45.8, 90.0, 20.0, 7.7, 1.0, 15.0};
    BodyArray bodyArray = BodyArray(bodies);
    REQUIRE(bodyArray.posX(0) == 5.0);
    REQUIRE(bodyArray.posX(1) == -45.8);
    REQUIRE(bodyArray.posX(2) == 7.7);
    REQUIRE(bodyArray.posY(0) == 145.7);
    REQUIRE(bodyArray.posY(1) == 90.0);
    REQUIRE(bodyArray.posY(2) == 1.0);
    REQUIRE(bodyArray.mass(0) == 10.0);
    REQUIRE(bodyArray.mass(1) == 20.0);
    REQUIRE(bodyArray.mass(2) == 15.0);
}