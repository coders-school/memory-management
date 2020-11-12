
#include "../Scooter.hpp"
#include "../SharedPtr.hpp"
#include "catch.hpp"
#include <vector>

SCENARIO("Testing all SharedPtr functions") {

  GIVEN("SharedPtr with int = 200") {
    int *power = new int{200};
    SharedPtr<int> SharedPower(power);

    WHEN("using get() to get int value") {
      auto result = SharedPower.get();
      THEN("int given is equal to int from get()") { REQUIRE(result == power); }
    }

    WHEN("Using move constructor from SharedPtr") {
      REQUIRE(SharedPower.use_count() == 1);
      SharedPtr<int> NewSharedPower(std::move(SharedPower));
      THEN("New Shared has value from old one, old one is nullptr") {
        REQUIRE(*(NewSharedPower.get()) == *power);
        REQUIRE(SharedPower.get() == nullptr);
        REQUIRE(NewSharedPower.use_count() == 1);
      }
    }

    WHEN("Using copy constructor from SharedPtr") {
      SharedPtr<int> NewSharedPower(SharedPower);
      THEN("New Shared has value from old one, old one is intact, use count = "
           "2") {
        REQUIRE(*(NewSharedPower.get()) == *power);
        REQUIRE(*(SharedPower.get()) == *power);
        REQUIRE(SharedPower.use_count() == 2);
      }
    }

    WHEN("dereferencing SharedPtr with "
         "*"
         " to get member power_") {
      auto result = *SharedPower;
      THEN("value inside SharedPtr is same value as passed") {
        REQUIRE(result == *power);
      }
    }
  }

  GIVEN("SharedPtr with Scooter(power) where power = 100") {
    int power{100};
    SharedPtr<Scooter> scooter(new Scooter(power));
    WHEN("dereferencing SharedPtr with "
         "->"
         " to get member power_") {
      auto result = scooter->power_;
      THEN("value inside SharedPtr is same value as passed") {
        REQUIRE(result == power);
      }
    }
  }

  GIVEN("Two SharedPtr with different int=100 and int=200") {
    int *power1 = new int{100};
    SharedPtr<int> SharedPower1(power1);
    int *power2 = new int{200};
    SharedPtr<int> SharedPower2(power2);

    WHEN("using copy assignment operator from SharedPtr") {
      SharedPower1 = SharedPower2;
      THEN("Both SharedPtr has int=200, and count() = 2") {
        REQUIRE(*(SharedPower1.get()) == *power2);
        REQUIRE(SharedPower1.use_count() == 2);
      }
    }
  }

  GIVEN("Empty SharedPtr") {
    SharedPtr<int> Number(nullptr);
    WHEN("Get is returning nullptr") {
      auto result = Number.get();
      THEN("empty SharedPtr is returning nullptr through get()") {
        REQUIRE(result == nullptr);
      }
    }
  }

  GIVEN("SharedPtr with Scooter(insertValue) where power = 100") {
    int power{100};
    SharedPtr<int> scooter(new int(power));
    WHEN("Assigning poiter to bool variable") {
      bool result = scooter;
      THEN("When not empty, gives true") { REQUIRE(result); }
    }
  }
  GIVEN("Empty SharedPtr scooter") {
    SharedPtr<Scooter> scooter(nullptr);
    WHEN("Assigning a pointer to bool variable") {
      bool result = scooter;
      THEN("When not empty, gives true") { REQUIRE_FALSE(result); }
    }
  }

  GIVEN("Two Shared Ptr, one empty, one not") {
    int power{100};
    SharedPtr<int> OldSharedPtr(new int(power));
    SharedPtr<int> NewSharedPtr(nullptr);
    REQUIRE(OldSharedPtr.use_count() == 1);
    REQUIRE(NewSharedPtr.use_count() == 1);
    WHEN("Using move assignment operator from SharedPtr") {
      NewSharedPtr = std::move(OldSharedPtr);
      THEN("Switched ownership from OldSharedPtr to NewSharedPtr") {
        REQUIRE(NewSharedPtr.use_count() == 1);
        REQUIRE(*(NewSharedPtr.get()) == power);
        REQUIRE(OldSharedPtr.get() == nullptr);
      }
    }
  }

  GIVEN("One SharedPtr and one RawPtr") {
    int power1{100};
    int power2{200};
    SharedPtr<int> SharedOne(new int(power1));
    int *Power2Ptr = new int(power2);
    WHEN("Using reset to insert NewScooter") {
      SharedOne.reset(Power2Ptr);
      THEN("scooter has power of NewScooter") {
        REQUIRE(*(SharedOne.get()) == power2);
      }
    }
  }
}
