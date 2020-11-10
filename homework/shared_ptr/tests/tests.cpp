
#include <vector>
#include "../Scooter.hpp"
#include "../SharedPtr.hpp"
#include "catch.hpp"

SCENARIO("Testing all SharedPtr functions")
{

    GIVEN("SharedPtr with int = 200")
    {
        int *power = new int{200};
        SharedPtr<int> SharedPower(power);
        WHEN("using get() to get int value")
        {
            auto result = SharedPower.get();
            THEN("int given is equal to int from get()")
            {
                REQUIRE(result == power);
            }
        }
    }

    GIVEN("SharedPtr with int = 200")
    {
        int *power = new int{200};
        SharedPtr<int> SharedPower(power);
        WHEN("Using move constructor from SharedPtr")
        {
            SharedPtr<int> NewSharedPower(std::move(SharedPower));
            THEN("New Shared has value from old one, old one is nullptr")
            {
                REQUIRE(*(NewSharedPower.get()) == *power);
                REQUIRE(SharedPower.get() == nullptr);
            }
        }
    }

    GIVEN("SharedPtr with int = 200")
    {
        int *power = new int{200};
        SharedPtr<int> SharedPower(power);
        WHEN("Using copy constructor from SharedPtr")
        {
            SharedPtr<int> NewSharedPower(SharedPower);
            THEN("New Shared has value from old one, old one is intact, use count = 2")
            {
                REQUIRE(*(NewSharedPower.get()) == *power);
                REQUIRE(*(SharedPower.get()) == *power);
                REQUIRE(SharedPower.use_count() == 2);
            }
        }
    }

    GIVEN("SharedPtr with int = 200")
    {
        int *power = new int{200};
        SharedPtr<int> SharedPower(power);
        WHEN(
            "dereferencing SharedPtr with "
            "*"
            " to get member power_")
        {
            auto result = *SharedPower;
            THEN("value inside SharedPtr is same value as passed")
            {
                REQUIRE(result == *power);
            }
        }
    }

    GIVEN("SharedPtr with Scooter(power) where power = 100")
    {
        int power{100};
        SharedPtr<Scooter> scooter(new Scooter(power));
        WHEN(
            "dereferencing SharedPtr with "
            "->"
            " to get member power_")
        {
            auto result = scooter->power_;
            THEN("value inside SharedPtr is same value as passed")
            {
                REQUIRE(result == power);
            }
        }
    }

    GIVEN("Two SharedPtr with different int=100 and int=200")
    {
        int *power1 = new int{100};
        SharedPtr<int> SharedPower1(power1);
        int *power2 = new int{200};
        SharedPtr<int> SharedPower2(power2);

        WHEN("using copy assigment operator from SharedPtr")
        {
            SharedPower1 = SharedPower2;
            THEN("Both SharedPtr has int=200, and count() = 2")
            {
                REQUIRE(*(SharedPower1.get()) == *power2);
                REQUIRE(*(SharedPower2.get()) == *power2);
                REQUIRE(SharedPower1.use_count() == 2);
            }
        }
    }

    GIVEN("Empty SharedPtr")
    {
        SharedPtr<int> scooter(nullptr);
        WHEN("Get is returning nullptr")
        {
            auto result = scooter.get();
            THEN("empty SharedPtr is returning nullptr through get()")
            {
                REQUIRE(result == nullptr);
            }
        }
    }

    GIVEN("SharedPtr with int = 100")
    {
        int power1{100};
        int power2{200};
        SharedPtr<int> SharedPower1(new int(power1));
        WHEN("resetting scooter with TurboScooter")
        {
            int *SharedPower2 = new int(power2);
            SharedPower1.reset(SharedPower2);

            THEN("ControlBlock Shared Counter is still = 1")
            {
                REQUIRE(*(SharedPower1.get()) == power2);
                REQUIRE(SharedPower1.use_count() == 1);
            }
        }
    }
    
    GIVEN("SharedPtr with Scooter(insertValue) where power = 100")
    {
        int power{100};
        SharedPtr<Scooter> scooter(new Scooter(power));
        bool result;
        WHEN("Assigning poiter to bool variable")
        {
            result = scooter;
            THEN("When not empty, gives true") { REQUIRE(result); }
        }
    }
    GIVEN("Empty SharedPtr scooter")
    {
        SharedPtr<Scooter> scooter(nullptr);
        bool result;
        WHEN("Assigning poiter to bool variable")
        {
            result = scooter;
            THEN("When not empty, gives true") { REQUIRE_FALSE(result); }
        }
    }

    GIVEN("Two Shared Ptr, one empty, one not")
    {
        int power{100};
        SharedPtr<Scooter> scooter(new Scooter(power));
        SharedPtr<Scooter> NewScooter(nullptr);
        WHEN("Using move assignment operator from SharedPtr")
        {
            NewScooter = std::move(scooter);
            THEN("ControlBlock Shared Counter is incremented to 2")
            {
                REQUIRE(NewScooter.get()->power_ == power);
                REQUIRE(scooter.get() == nullptr);
            }
        }
    }

    GIVEN("One SharedPtr and one RawPtr")
    {
        int power1{100};
        int power2{200};
        SharedPtr<Scooter> scooter(new Scooter(power1));
        Scooter *NewScooter = new Scooter(power2);
        WHEN("Using reset to insert NewScooter")
        {
            scooter.reset(NewScooter);
            THEN("scooter has power of NewScooter")
            {
                REQUIRE(scooter.get()->power_ == power2);
            }
        }
    }
}
