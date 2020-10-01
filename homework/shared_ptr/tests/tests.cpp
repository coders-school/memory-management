
#include "../Scooter.hpp"
#include "../SharedPtr.hpp"
#include "catch.hpp"

SCENARIO("Testing all SharedPtr functions") {
  GIVEN("SharedPtr with Scooter(power) where power = 200") {
    int power{200};
    SharedPtr<Scooter> scooter(new Scooter(power));
    WHEN("getting insertValue from SharedPtr::get() function result") {
      auto result = scooter.get()->power_;
      THEN("power value inside SharedPtr is same value as passed one") {
        REQUIRE(result == power);
      }
    }
  }

  GIVEN("SharedPtr with Scooter(insertValue) where power = 100") {
    SharedPtr<Scooter> scooter(nullptr);
    WHEN("dereferencing SharedPtr and get member from Scooter object") {
      auto result = scooter.get();
      THEN("value inside SharedPtr is same value as passed insertValue") {
        REQUIRE(result == nullptr);
      }
    }
  }

  GIVEN("SharedPtr with Scooter(insertValue) where power = 100") {
    int power{100};
    SharedPtr<Scooter> scooter(new Scooter(power));
    WHEN("dereferencing SharedPtr and get member from Scooter object") {
      auto result = (*scooter).power_;
      THEN("value inside SharedPtr is same value as passed insertValue") {
        REQUIRE(result == power);
      }
    }
  }
  GIVEN("SharedPtr with Scooter(insertValue) where power = 100") {
    int power{100};
    SharedPtr<Scooter> scooter(new Scooter(power));
    WHEN("copying SharedPtr") {
      auto NewSharedPtr = scooter;
      THEN("ControlBlock Shared Counter is incremented to 1") {
        REQUIRE(*(scooter.ControlBlock.at(1)) == 1);
      }
    }
  }
}