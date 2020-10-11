#define CATCH_CONFIG_MAIN
#include "UniquePointer.hpp"
#include "TestingClass.hpp"

#include "catch.hpp"

SCENARIO("Using unique pointers", "[uniquePtr]")
{
    const int firstNumber{5};
    const int secondNumber{80};
    const int thirdNumber{400};

    const int fourthNumber{77};
    const int fifthNumber{123};
    const int sixthNumber{510214};

    GIVEN("Unique pointer to type int")
    {
        UniquePointer<int> ptr1(new int{firstNumber});
        UniquePointer<int> ptr2(new int{secondNumber});
        UniquePointer<int> ptr3(new int{thirdNumber});

        WHEN("Using operator*")
        {
            THEN("Should return value")
            {
                REQUIRE(*ptr1 == firstNumber);
                REQUIRE(*ptr2 == secondNumber);
                REQUIRE(*ptr3 == thirdNumber);
            }
        }

        WHEN("Using UniquePointer::get()")
        {
            int* rawPtr1 = ptr1.get();
            int* rawPtr2 = ptr2.get();
            int* rawPtr3 = ptr3.get();

            THEN("Should return raw pointer")
            {
                REQUIRE(*rawPtr1 == firstNumber);
                REQUIRE(*rawPtr2 == secondNumber);
                REQUIRE(*rawPtr3 == thirdNumber);
            }

            THEN("Shouldnt move memory managment to a raw pointer, just create a raw pointer")
            {
                REQUIRE(*ptr1 == firstNumber);
                REQUIRE_NOTHROW(*ptr1);
                REQUIRE(*ptr2 == secondNumber);
                REQUIRE_NOTHROW(*ptr2);
                REQUIRE(*ptr3 == thirdNumber);
                REQUIRE_NOTHROW(*ptr3);
            }
        }

        WHEN("Using UniquePointer::replace()")
        {
            int* rawPtr1 = ptr1.replace();
            int* rawPtr2 = ptr2.replace();
            int* rawPtr3 = ptr3.replace();

            THEN("Should return raw pointer")
            {
                REQUIRE(*rawPtr1 == firstNumber);
                REQUIRE(*rawPtr2 == secondNumber);
                REQUIRE(*rawPtr3 == thirdNumber);
            }

            THEN("Should throw exception when trying dereference because memory managment was move to a raw pointer")
            {
                REQUIRE_THROWS_AS(*ptr1, DereferenceNullPtr);
                REQUIRE_THROWS_AS(*ptr2, DereferenceNullPtr);
                REQUIRE_THROWS_AS(*ptr3, DereferenceNullPtr);
            }

            delete rawPtr1;
            delete rawPtr2;
            delete rawPtr3;
        }

        WHEN("Using UniquePointer::reset()")
        {
            ptr1.reset(new int{fourthNumber});
            ptr2.reset(new int{fifthNumber});
            ptr3.reset(new int{sixthNumber});

            THEN("Should return raw pointer")
            {
                REQUIRE(*ptr1 == fourthNumber);
                REQUIRE(*ptr2 == fifthNumber);
                REQUIRE(*ptr3 == sixthNumber);
            }

            THEN("Shouldnt throw exception because its a new memory alocated instead old which is free")
            {
                REQUIRE_NOTHROW(*ptr1);
                REQUIRE_NOTHROW(*ptr2);
                REQUIRE_NOTHROW(*ptr3);
            }
        }
    }
}