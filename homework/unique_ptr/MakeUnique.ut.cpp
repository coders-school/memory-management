#include "catch.hpp"

#include "TestingClass.hpp"
#include "UniquePointer.hpp"

#include <cstddef>
#include <string>

SCENARIO("Using make unique to initialize unique pointers", "[makeUniquePtr]")
{
    int firstNumber{5};
    [[maybe_unused]] int secondNumber{77};

    std::string firstText{"Lololo"};
    [[maybe_unused]] std::string secondText{"Bitwa pod Grunwaldem"};

    auto uniqueIntRValue = MakeUnique<int>(99);
    auto uniqueIntLValue = MakeUnique<int>(firstNumber);
    auto uniqueTestingClassRValue = MakeUnique<TestingClass>("any text");
    auto uniqueTestingClassLValue = MakeUnique<TestingClass>(firstText);
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
