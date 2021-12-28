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
