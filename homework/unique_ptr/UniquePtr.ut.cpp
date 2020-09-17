#include <gtest/gtest.h>
#include "UniquePtr.hpp"

class MoveTest : public testing::Test {
public:
    auto moveTest() {
        UniquePtr<int> ptr{new int{9}};
        return ptr;
    }
};

TEST(UniquePtrTest, DereferenceOperatorShouldReturnFive) {
    UniquePtr<int> unique{new int(5)};
    ASSERT_EQ(5, *unique);
}

TEST(UniquePtrTest, GetFunctionShouldReturnValueOfPointer) {
    UniquePtr<int> ptr{new int{3}};
    auto ptrNew = ptr.get();
    ASSERT_EQ(3, *ptrNew);
}

TEST(UniquePtrTest, AfterReleaseUniquePtrShouldHaveNullPtrInside) {
    UniquePtr<int> ptr{new int{4}};
    ptr.release();
    ASSERT_EQ(nullptr, ptr.get());
}

TEST_F(MoveTest, MoveConstructorTest) {
    UniquePtr<int> ptr{new int{30}};
    UniquePtr<int> secondPtr(std::move(ptr));

    ASSERT_EQ(ptr.get(), nullptr);
    ASSERT_EQ(30, *secondPtr.get());
}

TEST(UniquePtrTest, IfUniquePtrDereferenceNullPtrExceptionShouldBeThrown) {
    UniquePtr<int> ptr{nullptr};
    ASSERT_THROW(*ptr, NullPtrDereferenceException);
}

TEST(UniquePtrTest, IfResetIsUsedUniquePtrShouldContainNewValue) {
    UniquePtr<int> ptr{new int{10}};
    ptr.reset(new int{100});
    ASSERT_EQ(100, *ptr);
}

TEST_F(MoveTest, MoveAssignmentTest) {
    UniquePtr<int> ptr{new int{12}};
    ptr = moveTest();
    ASSERT_EQ(9, *ptr);
}
