#include "gtest/gtest.h"

#include "UniquePtr.hpp"

constexpr int pointerValue = 5;

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
