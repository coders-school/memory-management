
#include "../TestClass.hpp"
#include "../uniqueptr.hpp"
#include "catch.hpp"

SCENARIO("Working on home implemented unique_ptr") {

  GIVEN("Created FirstUniquePtr and PtrCollection") {
    double input1 = 2.0;
    double input2 = 3.0;
    unique_ptr<TestClass> firstUnique(new TestClass(input1));
    std::vector<unique_ptr<TestClass>> PtrCollection;

    REQUIRE(firstUnique.get()->data_ == input1);
    REQUIRE(firstUnique.get() != nullptr);

    WHEN("Reseting unique_ptr with new object and value") {
      firstUnique.reset(new TestClass(input2));
      THEN("new value in unique_ptr, and earlier called get() is empty") {
        REQUIRE(firstUnique.get()->data_ == input2);
      }
    }

    WHEN("Reseted uniqueptr with nullptr") {
      firstUnique.reset(nullptr);
      THEN("unique_ptr is nullptr") { REQUIRE(firstUnique.get() == nullptr); }
    }
    WHEN("Moving into another container") {
      firstUnique.reset(new TestClass(input2));
      PtrCollection.push_back(std::move(firstUnique));
      THEN("Check if there are new parameters") {
        REQUIRE(PtrCollection.at(0).get()->data_ == input2);
        REQUIRE(firstUnique.get() == nullptr);
      }
    }
    WHEN("Moving into another null_ptr ") {
      unique_ptr<TestClass> secondUnique = std::move(firstUnique);
      THEN("Check if there are new parameters") {
        REQUIRE(firstUnique.get() == nullptr);
        REQUIRE(secondUnique.get()->data_ == input1);
      }
    }
  }
}