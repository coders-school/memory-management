#include <gtest/gtest.h>
#include "UniquePtr.hpp"

class MoveTest : public testing::Test {
public:
    auto moveTest() {
        UniquePtr<int> ptr{new int{9}};
        return ptr;
    }
};

TEST(UniquePtrTest, UniquePointerDereferenceOperatorShouldReturnValue) {
    UniquePtr<int> ptr{new int{5}};
    ASSERT_EQ(5, *ptr);
}

TEST(UniquePtrTest, UniquePtrAfterResetShouldContainNewValue) {
    UniquePtr<int> ptr{new int{5}};
    ptr.reset(new int{99});
    ASSERT_EQ(99, *ptr);
}

TEST(UniquePtrTest, UniquePtrGetShouldGiveUsValueOfPointer) {
    UniquePtr<int> ptr{new int{5}};
    auto newPtr = ptr.get();
    ASSERT_EQ(5, *newPtr);
}

TEST(UniquePtrTest, UniquePtrAfterReleaseShouldBeNullptr) {
    UniquePtr<int> ptr{new int{5}};
    ptr.release();
    ASSERT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtrTest, DereferenceOfNullptrShouldReturnException) {
    UniquePtr<int> ptr{nullptr};
    ASSERT_THROW(*ptr, NullptrDereferenceError);
}

TEST_F(MoveTest, MoveConstructorTest) {
    UniquePtr<int> ptr{moveTest()};
    ASSERT_EQ(9, *ptr);
}

TEST_F(MoveTest, MoveAssignmentTest) {
    UniquePtr<int> ptr{new int{12}};
    ptr = moveTest();
    ASSERT_EQ(9, *ptr);
}
