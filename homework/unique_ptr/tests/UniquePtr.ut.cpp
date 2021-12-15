#include "gtest/gtest.h"

#include "UniquePtr.hpp"

TEST(UniquePtr, DefaultConstructorShouldInitializePointerWithNullPtrValue)
{
    my_pointer::unique_ptr<int> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
}
