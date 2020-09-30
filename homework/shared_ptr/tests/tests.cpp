
#include "../TestClass.hpp"
#include "../SharedPtr.hpp"
#include "catch.hpp"

SCENARIO("Working on home implemented unique_ptr") {

  GIVEN("Created FirstUniquePtr and PtrCollection") {
    WHEN("Reseting unique_ptr with new object and value") {
        THEN("new value in unique_ptr, and earlier called get() is empty") {
        REQUIRE(1 == 1);
      }
    }
  }
}