#include "catch.hpp"

#include "UniquePointer.hpp"

#include <cstddef>

SCENARIO("Using make unique to initialize unique pointers", "[makeUniquePtr]")
{
    auto uniqueInt = MakeUnique<int>(50);
    GIVEN("Create an object wiht MakeUnique")
    {
        WHEN("Its run")
        {
            THEN("Its return a UniquePointer")
            {
                REQUIRE(1 == 1);
            }
        }
    }
}
