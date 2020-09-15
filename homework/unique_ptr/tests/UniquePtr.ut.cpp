#include <gtest/gtest.h>
#include "UniquePtr.hpp"

TEST(UniquePtrTest, ShouldReturnTrue) {
    ASSERT_TRUE(true);
}

TEST(UniquePtrTest, UniquePointerDereferenceOperatorShouldReturnValue) {
    UniquePtr<int> ptr{new int{5}};
    ASSERT_EQ(5, *ptr);
}

TEST(UniquePtrTest, UniquePtrAfterResetShouldContainNewValue) {
    UniquePtr<int> ptr{new int{5}};
    ptr.reset(new int{99});
    ASSERT_EQ(99, *ptr);
}

TEST(UniquePtrTest, UniquePtrAfterReleaseShouldBeNullptr) {
    UniquePtr<int> ptr{new int{5}};
    ptr.release();
    ASSERT_EQ(ptr.get(), nullptr);
}
