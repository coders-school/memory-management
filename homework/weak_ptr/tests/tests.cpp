#include "../Scooter.hpp"
#include "../WeakPtr.hpp"
#include "catch.hpp"

SCENARIO("Testing all WeakPtr functions") {
    GIVEN("SharedPtr of Scooter with Power = 200") {
        int power{200};
        SharedPtr<Scooter> sharedscooter(new Scooter(power));
        WHEN("making a WeakPtr from SharedPtr") {
            WeakPtr<Scooter> weakscooter(sharedscooter);
            THEN("made a WeakPtr without any problems") {
                REQUIRE(Catch::isOk);
            }
        }
    }

    GIVEN("SharedPtr of Scooter with Power = 200") {
        int power{200};
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
        int power{200};
        SharedPtr<Scooter> sharedscooter1(new Scooter(power));
        SharedPtr<Scooter> sharedscooter2(sharedscooter1);
        SharedPtr<Scooter> sharedscooter3(sharedscooter1);
        WHEN("making a WeakPtr from SharedPtr") {
            WeakPtr<Scooter> weakscooter(sharedscooter1);
            THEN("useCount should return 2 and useWeakCount should return 1") {
                REQUIRE(weakscooter.useCount() == 3);
                REQUIRE(weakscooter.useWeakCount() == 1);
            }
        }
    }

    // GIVEN("WeakPtr made from SharedPtr of Scooter with Power = 200") {
    //     int power{200};
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