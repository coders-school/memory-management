#include "../Scooter.hpp"
#include "../WeakPtr.hpp"
#include "catch.hpp"

constexpr size_t power = 200;

SCENARIO("Testing all WeakPtr functions") {
    GIVEN("SharedPtr of Scooter with Power = 200") {
        SharedPtr<Scooter> sharedscooter(new Scooter(power));
        WHEN("making a WeakPtr from SharedPtr") {
            WeakPtr<Scooter> weakscooter(sharedscooter);
            THEN("made a WeakPtr without any problems") {
                REQUIRE(Catch::isOk);
            }
        }
    }

    GIVEN("SharedPtr of Scooter with Power = 200") {
        SharedPtr<Scooter> sharedscooter(new Scooter(power));
        WHEN("making a WeakPtr from SharedPtr") {
            WeakPtr<Scooter> weakscooter(sharedscooter);
            THEN("shared counter equals 1 and weak counter equals 1") {
                REQUIRE(weakscooter.useCount() == 1);
                REQUIRE(weakscooter.useWeakCount() == 1);
            }
        }
    }

    GIVEN("Two SharedPtrs") {
        SharedPtr<Scooter> sharedscooter(new Scooter(power));
        SharedPtr<Scooter> sharedscooter2(sharedscooter);
        SharedPtr<Scooter> sharedscooter3(sharedscooter);
        WHEN("making a WeakPtr from SharedPtr") {
            WeakPtr<Scooter> weakscooter(sharedscooter);
            THEN("useCount should return 2 and useWeakCount should return 1") {
                REQUIRE(weakscooter.useCount() == 3);
                REQUIRE(weakscooter.useWeakCount() == 1);
            }
        }
    }

    GIVEN("SharedPtr of Scooter with Power = 200") {
        SharedPtr<Scooter> sharedscooter(new Scooter(power));
        WHEN("making a WeakPtr") {
            WeakPtr<Scooter> weakscooter(sharedscooter);
            THEN("WeakPtr shouldn't expired") {
                REQUIRE(weakscooter.expired() == false);
            }
        }
    }

    // GIVEN("WeakPtr made from SharedPtr of Scooter with Power = 200") {
    //     SharedPtr<Scooter> sharedscooter(new Scooter(power));
    //     WeakPtr<Scooter> weakscooter(sharedscooter);
    //     WHEN("removing the object") {
    //         weakscooter.reset();
    //         THEN("WeakPtr should expired") {
    //             REQUIRE(weakscooter.expired() == true);
    //         }
    //     }
    // }

}