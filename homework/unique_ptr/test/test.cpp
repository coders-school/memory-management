#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch_amalgamated.hpp"
#include "../uniquePTR.hpp"
#include <type_traits>

SCENARIO("Testing unique pointer - copy")
{
    GIVEN("Two scenarios")
    {
        WHEN("Checking if it is possible to copy by copy constructor")
        {
            auto copy = std::is_copy_constructible<unique_ptr<int>>::value;
            THEN("Result should be false")
            {
                REQUIRE_FALSE(copy);
            }
        }
        WHEN("Checking if it is possible to copy by copy assignment operator")
        {
            auto copy2 = std::is_copy_assignable<unique_ptr<int>>::value;
            THEN("Result should be false")
            {
                REQUIRE_FALSE(copy2);
            }
        }
    }
}

SCENARIO("Testing unique pointer - move")
{
    GIVEN("Two scenarios")
    {
        WHEN("Checking if it is possible to move by move constructor")
        {
            auto move = std::is_move_constructible<unique_ptr<int>>::value;
            THEN("Result should be true")
            {
                REQUIRE(move);
            }
        }
        WHEN("Checking if it is possible to move by move assignment operator")
        {
            auto move2 = std::is_move_assignable<unique_ptr<int>>::value;
            THEN("Result should be true")
            {
                REQUIRE(move2);
            }
        }
    }
}

SCENARIO("Testing unique pointer - operators")
{
    GIVEN("Two scenarios")
    {
        WHEN("Checking overloading operator*()")
        {
            auto unique1 = unique_ptr<int>(new int (5));
            auto operator1 = *unique1;
            THEN("Value of operator1 should be equal to 5")
            {
                CHECK(operator1 == 5);
            }
        }
        // WHEN("Checking overloading operator->()")
        // {
        //     auto operator2 = std::is_move_assignable<unique_ptr<int>>::value;
        //     THEN("Result should be true")
        //     {
        //         REQUIRE(move2);
        //     }
        // }
    }
}