
#include "../Scooter.hpp"
#include "../SharedPtr.hpp"
#include "catch.hpp"
#include <vector>
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
    WHEN("Using move constructor from SharedPtr") {
      std::vector<SharedPtr<Scooter>> NewScooterVector;
      NewScooterVector.push_back(std::move(scooter));
      THEN("ControlBlock SharedCounter is still with same value") {
        REQUIRE(NewScooterVector.at(0).get()->power_ == power);
        REQUIRE(NewScooterVector.at(0).use_count() == 1);
      }
    }
  }
  GIVEN("SharedPtr with Scooter(insertValue) where power = 100") {
    int power{100};
    SharedPtr<Scooter> scooter(new Scooter(power));
    WHEN("Using copy constructor from SharedPtr") {
      std::vector<SharedPtr<Scooter>> NewScooterVector;
      NewScooterVector.push_back(scooter);
      THEN("ControlBlock Shared Counter is incremented to 2") {
        REQUIRE(NewScooterVector.at(0).get()->power_ == power);
        REQUIRE(NewScooterVector.at(0).use_count() == 2);
      }
    }
  }
  GIVEN("SharedPtr with Scooter(insertValue) where power = 100") {
    int power{100};
    SharedPtr<Scooter> scooter(new Scooter(power));
    WHEN("using copy assigment operator from SharedPtr") {
      SharedPtr<Scooter> NewScooter = scooter;
      THEN("ControlBlock Shared Counter is incremented to 2") {
        REQUIRE(NewScooter.get()->power_ == power);
        REQUIRE(NewScooter.use_count() == 2);
      }
    }
  }
  GIVEN("SharedPtr with Scooter(insertValue) where power = 100") {
    int power{100};
    int TurboPower{200};
    SharedPtr<Scooter> scooter(new Scooter(power));
    WHEN("resetting scooter with TurboScooter") {
      Scooter* TurboScooter = new Scooter(TurboPower);
      scooter.reset(TurboScooter);
      THEN("ControlBlock Shared Counter is still = 1") {
        REQUIRE(scooter.get()->power_ == TurboPower);
        REQUIRE(scooter.use_count() == 1);
      }
    }
  }
}
