#define CATCH_CONFIG_MAIN
#include "TestingClass.hpp"
#include "UniquePointer.hpp"

#include "catch.hpp"

#include <cstddef>

SCENARIO("Using unique pointers", "[uniquePtr]")
{
    const int firstNumber{5};

    const int secondNumber{77};

    std::string firstText{"Lololo"};

    std::string secondText{"Bitwa pod Grunwaldem"};

    GIVEN("Unique pointer to type int")
    {
        UniquePointer<int> ptr1(new int{firstNumber});

        WHEN("Using operator*")
        {
            THEN("Should return value")
            {
                REQUIRE(*ptr1 == firstNumber);
            }
        }

        WHEN("Using move constructor")
        {
            UniquePointer<int> anyPtr = std::move(ptr1);

            THEN("Should create unique pointer using move constructor and free memory")
            {
                REQUIRE(ptr1.get() == nullptr);
                REQUIRE(*anyPtr == firstNumber);
            }
        }

        WHEN("Using move assigment operator")
        {
            UniquePointer<int> anyPtr;
            anyPtr = std::move(ptr1);

            THEN("Should move data to a new pointer using move assigment operator and free memory")
            {
                REQUIRE(ptr1.get() == nullptr);
                REQUIRE(*anyPtr == firstNumber);
            }
        }

        WHEN("Using UniquePointer::get()")
        {
            int* rawPtr1 = ptr1.get();

            THEN("Should return raw pointer")
            {
                REQUIRE(*rawPtr1 == firstNumber);
            }

            THEN("Shouldnt move memory managment to a raw pointer, just create a raw pointer")
            {
                REQUIRE(*ptr1 == firstNumber);
                REQUIRE_NOTHROW(*ptr1);
            }
        }

        WHEN("Using UniquePointer::release()")
        {
            int* rawPtr1 = ptr1.release();

            THEN("Should return raw pointer")
            {
                REQUIRE(*rawPtr1 == firstNumber);
            }

            THEN("Should throw exception when trying dereference because memory managment was move to a raw pointer")
            {
                REQUIRE_THROWS_AS(*ptr1, DereferenceNullPtr);
            }

            delete rawPtr1;
        }

        WHEN("Using UniquePointer::reset()")
        {
            ptr1.reset(new int{secondNumber});

            THEN("Should return raw pointer")
            {
                REQUIRE(*ptr1 == secondNumber);
            }

            THEN("Shouldnt throw exception because its a new memory alocated instead old which is free")
            {
                REQUIRE_NOTHROW(*ptr1);
            }
        }

        WHEN("Using UniquePointer::get()")
        {
            int* rawPtr1 = ptr1.get();

            THEN("Should return raw pointer")
            {
                REQUIRE(*rawPtr1 == firstNumber);
            }

            THEN("Shouldnt move memory managment to a raw pointer, just create a raw pointer")
            {
                REQUIRE(*ptr1 == firstNumber);
                REQUIRE_NOTHROW(*ptr1);
            }
        }

        WHEN("Using UniquePointer::release()")
        {
            int* rawPtr1 = ptr1.release();

            THEN("Should return raw pointer")
            {
                REQUIRE(*rawPtr1 == firstNumber);
            }

            THEN("Should throw exception when trying dereference because memory managment was move to a raw pointer")
            {
                REQUIRE_THROWS_AS(*ptr1, DereferenceNullPtr);
            }

            delete rawPtr1;
        }

        WHEN("Using UniquePointer::reset() with argument")
        {
            ptr1.reset(new int{secondNumber});

            THEN("Should create a new class object on a heap and free old one memory")
            {
                REQUIRE(*ptr1 == secondNumber);
            }

            THEN("Shouldnt throw exception because its a new memory alocated instead old which is free")
            {
                REQUIRE_NOTHROW(*ptr1);
            }
        }

        WHEN("Using UniquePointer::reset() without argument")
        {
            ptr1.reset();

            THEN("Should free memory")
            {
                REQUIRE(ptr1.get() == nullptr);
            }

            THEN("Should throw exception because memory is free and pointer is set as nullptr")
            {
                REQUIRE_THROWS_AS(*ptr1, DereferenceNullPtr);
            }
        }
    }

    GIVEN("Unique pointer to testing class")
    {
        UniquePointer<TestingClass> ptr1(new TestingClass{firstText});

        WHEN("Using operator->")
        {
            THEN("Should return value")
            {
                REQUIRE(ptr1->testingGetter() == firstText);
            }
        }

        WHEN("Using move constructor")
        {
            UniquePointer<TestingClass> anyPtr = std::move(ptr1);

            THEN("Should create unique pointer using move constructor and free memory")
            {
                REQUIRE(ptr1.get() == nullptr);
                REQUIRE(anyPtr->testingGetter() == firstText);
            }
        }

        WHEN("Using move assigment operator")
        {
            UniquePointer<TestingClass> anyPtr;
            anyPtr = std::move(ptr1);

            THEN("Should move data to a new pointer using move assigment operator and free memory")
            {
                REQUIRE(ptr1.get() == nullptr);
                REQUIRE(anyPtr->testingGetter()  == firstText);
            }
        }

        WHEN("Using UniquePointer::get()")
        {
            TestingClass* rawPtr1 = ptr1.get();

            THEN("Should return raw pointer")
            {
                REQUIRE(rawPtr1->testingGetter() == firstText);
            }

            THEN("Shouldnt move memory managment to a raw pointer, just create a raw pointer")
            {
                REQUIRE(ptr1->testingGetter() == firstText);
                REQUIRE_NOTHROW(ptr1->testingGetter());
            }
        }

        WHEN("Using UniquePointer::release()")
        {
            TestingClass* rawPtr1 = ptr1.release();

            THEN("Should return raw pointer")
            {
                REQUIRE(rawPtr1->testingGetter() == firstText);
            }

            THEN("Should throw exception when trying use operator-> because memory managment was move to a raw pointer")
            {
                REQUIRE_THROWS_AS(ptr1->testingGetter(), DereferenceNullPtr);
            }

            delete rawPtr1;
        }

        WHEN("Using UniquePointer::reset() with argument")
        {
            ptr1.reset(new TestingClass{secondText});

            THEN("Should create a new class object on a heap and free old one memory")
            {
                REQUIRE(ptr1->testingGetter() == secondText);
            }

            THEN("Shouldnt throw exception because its a new memory alocated instead old which is free")
            {
                REQUIRE_NOTHROW(ptr1->testingGetter());
            }
        }

        WHEN("Using UniquePointer::reset() without argument")
        {
            ptr1.reset();

            THEN("Should free memory")
            {
                REQUIRE(ptr1.get() == nullptr);
            }

            THEN("Should throw exception because memory is free and pointer is set as nullptr")
            {
                REQUIRE_THROWS_AS(*ptr1, DereferenceNullPtr);
            }
        }
    }
}
