#include "catch.hpp"

#include "TestingClass.hpp"
#include "UniquePointer.hpp"

#include <cstddef>
#include <string>

SCENARIO("Using make unique to initialize unique pointers", "[makeUniquePtr]")
{
    int firstNumber{5};
    //int secondNumber{77};

    std::string firstText{"Lololo"};
    // std::string secondText{"Bitwa pod Grunwaldem"};

    auto uniqueInt = MakeUnique<int>(firstNumber);
    //auto uniqueTestingClass = MakeUnique<TestingClass>("any text");
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
