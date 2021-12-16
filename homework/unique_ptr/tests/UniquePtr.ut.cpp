#include "gtest/gtest.h"

#include "UniquePtr.hpp"

constexpr int pointerValue = 5;
constexpr int classValue = 42;

class ArrowOperatorTest {
public:
    int getTestValue() const
    {
        return testValue_;
    }

private:
    const int testValue_ { classValue };
};

TEST(UniquePtr, DefaultConstructorShouldInitializePointerWithNullPtrValue)
{
    my_pointer::unique_ptr<int> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtr, ConstructorShouldTakePointerAndThenOwnsIt)
{
    my_pointer::unique_ptr<int> ptr { new int { pointerValue } };
    EXPECT_EQ(*ptr.get(), pointerValue);
}

TEST(UniquePtr, DereferenceOperatorShouldProvideAccessToObject)
{
    my_pointer::unique_ptr<int> ptr { new int { pointerValue } };
    EXPECT_EQ(*ptr, pointerValue);
}

TEST(UniquePtr, BoolOperatorShouldCheckWhetherPointerOwnsAnObject)
{
    my_pointer::unique_ptr<int> ptr { new int { pointerValue } };
    EXPECT_TRUE(ptr);
    my_pointer::unique_ptr<int> ptr2 {};
    EXPECT_FALSE(ptr2);
}

TEST(UniquePtr, ResetFunctionWithProvidedPointerShouldChangePointerValueToProvided)
{
    my_pointer::unique_ptr<int> ptr {};
    EXPECT_EQ(ptr.get(), nullptr);

    ptr.reset(new int { pointerValue });
    EXPECT_EQ(*ptr, pointerValue);
}

TEST(UniquePtr, ResetFunctionWithoutProvidedPointerShouldChangePointerValueToNullptr)
{
    my_pointer::unique_ptr<int> ptr { new int { pointerValue } };
    EXPECT_EQ(*ptr, pointerValue);

    ptr.reset();
    EXPECT_FALSE(ptr);
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtr, ReleaseFunctionShouldReleaseTheOwnershipOfManagedObject)
{
    my_pointer::unique_ptr<int> ptr { new int { pointerValue } };
    int* releasedPtr = ptr.release();
    EXPECT_FALSE(ptr);
    EXPECT_EQ(ptr.get(), nullptr);

    EXPECT_TRUE(releasedPtr);
    EXPECT_EQ(*releasedPtr, pointerValue);
    delete releasedPtr;
}

TEST(UniquePtr, MoveConstructorShouldConstructNewPointerByTransferingOwnershipFromPassedPointer)
{
    my_pointer::unique_ptr<int> ptr { new int { pointerValue } };
    EXPECT_EQ(*ptr, pointerValue);

    auto movedPtr { std::move(ptr) };
    EXPECT_FALSE(ptr);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_TRUE(movedPtr);
    EXPECT_EQ(*movedPtr, pointerValue);
}

TEST(UniquePtr, MoveAssingmentSouldTransferOwnershipFromPassedPointer)
{
    my_pointer::unique_ptr<int> ptr { new int { pointerValue } };
    EXPECT_EQ(*ptr, pointerValue);

    my_pointer::unique_ptr<int> movedPtr;
    EXPECT_FALSE(movedPtr);

    movedPtr = std::move(ptr);

    EXPECT_FALSE(ptr);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_TRUE(movedPtr);
    EXPECT_EQ(*movedPtr, pointerValue);
}

TEST(UniquePtr, ArrowOperatorShouldProvideAccesToOwnedObject)
{
    my_pointer::unique_ptr<ArrowOperatorTest> ptr { new ArrowOperatorTest {} };
    EXPECT_EQ(ptr->getTestValue(), classValue);
}
