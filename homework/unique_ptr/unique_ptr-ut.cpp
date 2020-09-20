#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PtrIsNullptr.hpp"
#include "unique_ptr.hpp"

SCENARIO("TestUnique_ptr", "Unique_ptr"){

    const int StartValue = 10;
    const int NewValue = 12;

    GIVEN("InitializedUnique_ptr"){

        unique_ptr<int> ptr = new int{StartValue};

        WHEN("PtrIsInitialized"){
            THEN("ShouldCanReadTheContent"){
                CHECK(StartValue == *ptr);
            }
        }
        WHEN("AbleToDereferencePtr"){

            *ptr = NewValue;

            THEN("ShouldBeAbleToDereferencePtr"){
                CHECK(NewValue == *ptr);
            }
        }
        WHEN("MovePtr"){

            unique_ptr<int> ptr2 = std::move(ptr);

            THEN("ShouldMovePtr"){
                CHECK(*ptr2 == StartValue);
                CHECK(ptr.get() == nullptr);
            }
        }
        WHEN("MovePtrToPointerWhoHaveObject"){
            unique_ptr<int> ptr2 = new int{StartValue};

            ptr2 = std::move(ptr);

            THEN("ShouldMovePtr"){
                CHECK(*ptr2 == StartValue);
                CHECK(ptr.get() == nullptr);
            }
        }
        WHEN("UseResetMethod"){

            ptr.reset(new int{StartValue});

            THEN("ShouldUseReset"){
                CHECK(*ptr == StartValue);
            }
        }
        WHEN("UseGetMethod"){

            int* rptr = ptr.get();

            THEN("ShouldReturnRawPtr"){
                CHECK(*ptr == *rptr);
            }
        }
        WHEN("UseReleaseMethod"){

            auto p = ptr.release();

            THEN("ShouldUseReleaseMethod"){
                CHECK(*p == StartValue);
                CHECK(ptr.get() == nullptr);
            }
            delete p;
        }

    }
    GIVEN("UninitializedUnique_ptr"){

        unique_ptr<int> ptr;

        WHEN("TryReadValue"){
            THEN("ShoudThrowException"){
                CHECK_THROWS_AS(*ptr, PtrIsNullptr);
            }
        }
    }
    GIVEN("PointerTooStruct"){
        const int firstV = 3;
        const int secondV = 6;


        struct A {
            int foo() { return StartValue; }
            int value = firstV;
        };

        unique_ptr<A> ptr(new A{});

        WHEN("UseArrowOperatorToCallFunction"){
            THEN("ShouldCallAFunction"){
                CHECK(ptr->foo() == StartValue);
            }
        }
        WHEN("UseArrowOperatorToChangeMemberValue"){
            ptr->value = secondV;
            THEN("ShouldChangeMemberValue"){
                CHECK(ptr->value == secondV);
            }
        }
    }

}

