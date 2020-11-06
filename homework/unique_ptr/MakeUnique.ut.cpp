#include "catch.hpp"

#include "TestingClass.hpp"
#include "UniquePointer.hpp"

#include <cstddef>
#include <string>
#include <utility>

SCENARIO("Using make unique to initialize unique pointers", "[makeUniquePtr]")
{
    int firstNumber{5};
    [[maybe_unused]] int secondNumber{77};

    std::string firstText{"Lololo"};
    [[maybe_unused]] std::string secondText{"Bitwa pod Grunwaldem"};

    GIVEN("Creating an object with MakeUnique")
    {
        WHEN("Using MakeUnique<int>")
        {
            auto uniqueIntRValue = MakeUnique<int>(99);
            auto uniqueIntLValue = MakeUnique<int>(firstNumber);

            THEN("Should return an UniquePointer to int")
            {
                REQUIRE(*uniqueIntRValue == 99);
                REQUIRE(*uniqueIntLValue == firstNumber);
            }
        }

        WHEN("Using MakeUnique<TestingClass>")
        {
            auto uniqueTestingClassRValue = MakeUnique<TestingClass>("any text");
            auto uniqueTestingClassLValue = MakeUnique<TestingClass>(firstText);

            THEN("Should return an UniquePointer to TestingClass")
            {
                REQUIRE((*uniqueTestingClassRValue).testingGetter() == "any text");
                REQUIRE((*uniqueTestingClassLValue).testingGetter() == firstText);
            }
        }

        WHEN("Using MakeUnique<std::pair<std::string,int>>")
        {
            auto uniquePointerForMoreArguments = MakeUnique<std::pair<std::string, int>>("r value text", firstNumber);
            auto uniqueIntLValue = MakeUnique<int>(firstNumber);

            THEN("Should return an UniquePointer to std::pair<std::string,int>")
            {
                REQUIRE((*uniquePointerForMoreArguments).first == "r value text");
                REQUIRE((*uniquePointerForMoreArguments).second == firstNumber);
            }
        }

        WHEN("Using MakeUnique<int>()")
        {
            auto uniqueIntWithNoArgument = MakeUnique<int>();

            THEN("Should return an UniquePointer to int, TestingClass, std::pair")
            {
                REQUIRE(*uniqueIntWithNoArgument == 0);
            }
        }

        WHEN("Using MakeUnique<double[]>(10)")
        {
            unsigned arraySize = 10;
            auto uniqueDoubleArray = MakeUnique<double[]>(arraySize);

            for (unsigned i = 0; i < arraySize; i++) {
                uniqueDoubleArray[i] = arraySize;
            }

            THEN("Should return an UniquePointer to int, TestingClass, std::pair")
            {
                for (unsigned i = 0; i < arraySize; i++) {
                    REQUIRE(uniqueDoubleArray[i] == arraySize);
                }
            }
        }
    }
}
