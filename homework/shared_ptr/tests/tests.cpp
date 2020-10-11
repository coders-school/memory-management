
#include <vector>
#include "../Scooter.hpp"
#include "../SharedPtr.hpp"
#include "catch.hpp"

SCENARIO("Testing all SharedPtr functions") {
	
    GIVEN("SharedPtr with Scooter(power) where power = 200") {
        int power{200};
        SharedPtr<Scooter> scooter(new Scooter(power));
        WHEN("getting power from SharedPtr::get() function result") {
            auto result = scooter.getPtr()->power_;
            THEN("power value inside SharedPtr is same value as passed one") {
                REQUIRE(result == power);
            }
        }
    }

    GIVEN("SharedPtr with Scooter(power) where power = 100") {
        int power{100};
        SharedPtr<Scooter> scooter(new Scooter(power));
        WHEN("Using move constructor from SharedPtr") {
            std::vector<SharedPtr<Scooter>> NewScooterVector;
            NewScooterVector.push_back(std::move(scooter));
            THEN("ControlBlock SharedCounter is still with same value") {
                REQUIRE(NewScooterVector.size() == 1);
                REQUIRE(NewScooterVector.at(0).getPtr()->power_ == power);
            }
        }
    }

    GIVEN("SharedPtr with Scooter(power) where power = 100") {
        int power{100};
        SharedPtr<Scooter> scooter(new Scooter(power));
        WHEN("Using copy constructor from SharedPtr") {
            std::vector<SharedPtr<Scooter>> NewScooterVector;
            NewScooterVector.push_back(scooter);
            THEN("ControlBlock Shared Counter is incremented to 2") {
                REQUIRE(NewScooterVector.at(0).getPtr()->power_ == power);
                REQUIRE(NewScooterVector.at(0).use_count() == 2);
            }
        }
    }

    GIVEN("SharedPtr with Scooter(power) where power = 100") {
        int power{100};
        SharedPtr<Scooter> scooter(new Scooter(power));
        WHEN(
            "dereferencing SharedPtr with "
            "*"
            " to get member power_") {
            auto result = (*scooter).power_;
            THEN("value inside SharedPtr is same value as passed") {
                REQUIRE(result == power);
            }
        }
    }

    GIVEN("SharedPtr with Scooter(power) where power = 100") {
        int power{100};
        SharedPtr<Scooter> scooter(new Scooter(power));
        WHEN(
            "dereferencing SharedPtr with "
            "->"
            " to get member power_") {
            auto result = scooter->power_;
            THEN("value inside SharedPtr is same value as passed") {
                REQUIRE(result == power);
            }
        }
    }

    GIVEN("Two SharedPtr Scooters with different powers") {
        int power{100};
        int power2{150};
        SharedPtr<Scooter> scooter(new Scooter(power));
        SharedPtr<Scooter> scooter2(new Scooter(power2));
        WHEN("using copy assigment operator from SharedPtr") {
            scooter2 = scooter;
            THEN("ControlBlock of scooter SharedPtr is incremented to 2") {
                REQUIRE(scooter.getPtr()->power_ == power);
                REQUIRE(scooter.use_count() == 2);
            }
        }
    }

    GIVEN("Empty scooter SharedPtr") {
        SharedPtr<Scooter> scooter(nullptr);
        WHEN("Get is returning nullptr") {
            auto result = scooter.getPtr();
            THEN("empty SharedPtr is returning nullptr through get()") {
                REQUIRE(result == nullptr);
            }
        }
    }

    GIVEN("Two SharedPtr Scooters with different powers") {
        int power{100};
        int TurboPower{200};
        SharedPtr<Scooter> scooter(new Scooter(power));
        WHEN("resetting scooter with TurboScooter") {
            Scooter* TurboScooter = new Scooter(TurboPower);
            scooter.reset(TurboScooter);
            THEN("ControlBlock Shared Counter is still = 1") {
                REQUIRE(scooter.getPtr()->power_ == TurboPower);
                REQUIRE(scooter.use_count() == 1);
            }
        }
    }

    GIVEN("SharedPtr with Scooter(insertValue) where power = 100") {
        int power{100};
        SharedPtr<Scooter> scooter(new Scooter(power));
        bool result;
        WHEN("Assigning poiter to bool variable") {
            result = scooter;
            THEN("When not empty, gives true") { REQUIRE(result); }
        }
    }
    GIVEN("Empty SharedPtr scooter") {
        SharedPtr<Scooter> scooter(nullptr);
        bool result;
        WHEN("Assigning poiter to bool variable") {
            result = scooter;
            THEN("When not empty, gives true") { REQUIRE_FALSE(result); }
        }
    }

    GIVEN("Two Shared Ptr, one empty, one not") {
        int power{100};
        SharedPtr<Scooter> scooter(new Scooter(power));
        SharedPtr<Scooter> NewScooter(nullptr);
        WHEN("Using move assignment operator from SharedPtr") {
            NewScooter = std::move(scooter);
            THEN("ControlBlock Shared Counter is incremented to 2") {
                REQUIRE(NewScooter.getPtr()->power_ == power);
                REQUIRE(scooter.getPtr() == nullptr);
            }
        }
    }

    GIVEN("One SharedPtr and one RawPtr") {
        int power1{100};
        int power2{200};
        SharedPtr<Scooter> scooter(new Scooter(power1));
        Scooter* NewScooter = new Scooter(power2);
        WHEN("Using reset to insert NewScooter") {
            scooter.reset(NewScooter);
            THEN("scooter has power of NewScooter") {
                REQUIRE(scooter.getPtr()->power_ == power2);
            }
        }
    }
}
