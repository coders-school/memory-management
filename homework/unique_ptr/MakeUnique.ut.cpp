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

    GIVEN("Create an object wiht MakeUnique")
    {
        auto uniqueIntRValue = MakeUnique<int>(99);
        auto uniqueIntLValue = MakeUnique<int>(firstNumber);
        auto uniqueTestingClassRValue = MakeUnique<TestingClass>("any text");
        auto uniqueTestingClassLValue = MakeUnique<TestingClass>(firstText);

        WHEN("Using dereference")
        {
            THEN("Its return a reference to value or object")
            {
                REQUIRE(*uniqueIntRValue == 99);
                REQUIRE(*uniqueIntLValue == firstNumber);
                REQUIRE((*uniqueTestingClassRValue).testingGetter() == "any text");
                REQUIRE((*uniqueTestingClassLValue).testingGetter() == firstText);
            }
        }

        WHEN("Creating UniquePointer with std::move and object created by MakeUnique")
        {
            UniquePointer<int> uniqueIntRValue2(std::move(uniqueIntRValue));
            UniquePointer<int> uniqueIntLValue2(std::move(uniqueIntLValue));
            UniquePointer<TestingClass> uniqueTestingClassRValue2(std::move(uniqueTestingClassRValue));
            UniquePointer<TestingClass> uniqueTestingClassLValue2(std::move(uniqueTestingClassLValue));

            THEN("Should create unique pointer using move constructor and free memory")
            {
                REQUIRE(uniqueIntRValue.get() == nullptr);
                REQUIRE(*uniqueIntRValue2 == 99);

                REQUIRE(uniqueIntLValue.get() == nullptr);
                REQUIRE(*uniqueIntLValue2 == firstNumber);

                REQUIRE(uniqueTestingClassRValue.get() == nullptr);
                REQUIRE((*uniqueTestingClassRValue2).testingGetter() == "any text");

                REQUIRE(uniqueTestingClassLValue.get() == nullptr);
                REQUIRE((*uniqueTestingClassLValue2).testingGetter() == firstText);
            }
        }

        WHEN("Using move assigment operator with std::move and object created by MakeUnique")
        {
            UniquePointer<int> anyPtr;
            UniquePointer<int> anyPtr2;
            UniquePointer<TestingClass> anyPtr3;
            UniquePointer<TestingClass> anyPtr4;

            anyPtr = std::move(uniqueIntRValue);
            anyPtr2 = std::move(uniqueIntLValue);
            anyPtr3 = std::move(uniqueTestingClassRValue);
            anyPtr4 = std::move(uniqueTestingClassLValue);

            THEN("Should move data to a new pointer using move assigment operator and free memory")
            {
                REQUIRE(uniqueIntRValue.get() == nullptr);
                REQUIRE(*anyPtr == 99);
                REQUIRE(uniqueIntLValue.get() == nullptr);
                REQUIRE(*anyPtr2 == firstNumber);

                REQUIRE(uniqueTestingClassRValue.get() == nullptr);
                REQUIRE((*anyPtr3).testingGetter() == "any text");
                REQUIRE(uniqueTestingClassLValue.get() == nullptr);
                REQUIRE((*anyPtr4).testingGetter() == firstText);
            }
        }

        WHEN("Using UniquePointer::get()")
        {
            int* rawPtr1 = uniqueIntRValue.get();
            int* rawPtr2 = uniqueIntLValue.get();
            TestingClass* rawPtr3 = uniqueTestingClassRValue.get();
            TestingClass* rawPtr4 = uniqueTestingClassLValue.get();

            THEN("Should return raw pointer")
            {
                REQUIRE(*rawPtr1 == 99);
                REQUIRE(*rawPtr2 == firstNumber);
                REQUIRE((*rawPtr3).testingGetter() == "any text");
                REQUIRE((*rawPtr4).testingGetter() == firstText);
            }

            THEN("Shouldnt move memory managment to a raw pointer, just create a raw pointer")
            {
                REQUIRE_NOTHROW(*uniqueIntRValue);
                REQUIRE_NOTHROW(*uniqueIntLValue);
                REQUIRE_NOTHROW((*uniqueTestingClassRValue).testingGetter());
                REQUIRE_NOTHROW((*uniqueTestingClassLValue).testingGetter());
            }
        }

        WHEN("Using UniquePointer::release() with object created by MakeUnique")
        {
            int* rawPtr1 = uniqueIntRValue.release();
            int* rawPtr2 = uniqueIntLValue.release();
            TestingClass* rawPtr3 = uniqueTestingClassRValue.release();
            TestingClass* rawPtr4 = uniqueTestingClassLValue.release();

            THEN("Should return raw pointer")
            {
                REQUIRE(*rawPtr1 == 99);
                REQUIRE(*rawPtr2 == firstNumber);
                REQUIRE((*rawPtr3).testingGetter() == "any text");
                REQUIRE((*rawPtr4).testingGetter() == firstText);
            }

            THEN("Should throw exception when trying dereference because memory managment was move to a raw pointer")
            {
                REQUIRE_THROWS_AS(*uniqueIntRValue, DereferenceNullPtr);
                REQUIRE_THROWS_AS(*uniqueIntLValue, DereferenceNullPtr);
                REQUIRE_THROWS_AS((*uniqueTestingClassRValue).testingGetter(), DereferenceNullPtr);
                REQUIRE_THROWS_AS((*uniqueTestingClassLValue).testingGetter(), DereferenceNullPtr);
            }

            delete rawPtr1;
            delete rawPtr2;
            delete rawPtr3;
            delete rawPtr4;
        }

        WHEN("Using UniquePointer::reset() with argument, with object created by MakeUnique")
        {
            uniqueIntRValue.reset(new int(66));
            uniqueIntLValue.reset(new int(secondNumber));
            uniqueTestingClassRValue.reset(new TestingClass("something new!"));
            uniqueTestingClassLValue.reset(new TestingClass(secondText));

            THEN("Should create a new class object on a heap and free old one memory")
            {
                REQUIRE(*uniqueIntRValue == 66);
                REQUIRE(*uniqueIntLValue == secondNumber);
                REQUIRE((*uniqueTestingClassRValue).testingGetter() == "something new!");
                REQUIRE((*uniqueTestingClassLValue).testingGetter() == secondText);
            }

            THEN("Shouldnt throw exception because its a new memory alocated instead old which is free")
            {
                REQUIRE_NOTHROW(*uniqueIntRValue);
                REQUIRE_NOTHROW(*uniqueIntLValue);
                REQUIRE_NOTHROW((*uniqueTestingClassRValue).testingGetter());
                REQUIRE_NOTHROW((*uniqueTestingClassLValue).testingGetter());
            }
        }

        WHEN("Using UniquePointer::reset() without argument, with object created by MakeUnique")
        {
            uniqueIntRValue.reset();
            uniqueIntLValue.reset();
            uniqueTestingClassRValue.reset();
            uniqueTestingClassLValue.reset();

            THEN("Should free memory")
            {
                REQUIRE(uniqueIntRValue.get() == nullptr);
                REQUIRE(uniqueIntLValue.get() == nullptr);
                REQUIRE(uniqueTestingClassRValue.get() == nullptr);
                REQUIRE(uniqueTestingClassLValue.get() == nullptr);
            }

            THEN("Should throw exception because memory is free and pointer is set as nullptr")
            {
                REQUIRE_THROWS_AS(*uniqueIntRValue, DereferenceNullPtr);
                REQUIRE_THROWS_AS(*uniqueIntLValue, DereferenceNullPtr);
                REQUIRE_THROWS_AS((*uniqueTestingClassRValue).testingGetter(), DereferenceNullPtr);
                REQUIRE_THROWS_AS((*uniqueTestingClassLValue).testingGetter(), DereferenceNullPtr);
            }
        }
    }
}
