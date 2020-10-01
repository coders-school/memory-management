#include <gtest/gtest.h>
#include "UniquePtr.hpp"

constexpr int testedValue = 5;
constexpr int expectedValue = 5;

class MoveTest : public testing::Test {
public:
    auto moveTest() {
        UniquePtr<int> ptr{new int{testedValue}};
        return ptr;
    }
};

TEST(UniquePtrTest, DereferenceOperatorShouldReturnTestedValue) {
    UniquePtr<int> unique{new int(testedValue)};
    ASSERT_EQ(expectedValue, *unique);
}

TEST(UniquePtrTest, GetFunctionShouldReturnValueOfPointer) {
    UniquePtr<int> ptr{new int{testedValue}};
    auto ptrNew = ptr.get();
    ASSERT_EQ(expectedValue, *ptrNew);
}

TEST(UniquePtrTest, AfterReleaseUniquePtrShouldHaveNullPtrInside) {
    UniquePtr<int> ptr{new int{testedValue}};
    auto newPtr = ptr.release();
    delete newPtr;
    ASSERT_EQ(nullptr, ptr.get());
}

TEST_F(MoveTest, MoveConstructorTest) {
    UniquePtr<int> ptr{new int{testedValue}};
    UniquePtr<int> secondPtr(std::move(ptr));

    ASSERT_EQ(ptr.get(), nullptr);
    ASSERT_EQ(expectedValue, *secondPtr.get());
}

TEST(UniquePtrTest, IfUniquePtrDereferenceNullPtrExceptionShouldBeThrown) {
    UniquePtr<int> ptr{nullptr};
    ASSERT_THROW(*ptr, NullPtrDereferenceException);
}

TEST(UniquePtrTest, IfResetIsUsedUniquePtrShouldContainNewValue) {
    constexpr int newValue =  5;
    UniquePtr<int> ptr{new int{testedValue}};
    ptr.reset(new int{newValue});
    ASSERT_EQ(expectedValue, *ptr);
}

TEST_F(MoveTest, MoveAssignmentTest) {
    constexpr int firstValue = 12;
    UniquePtr<int> ptr{new int{firstValue}};
    ptr = moveTest();
    ASSERT_EQ(expectedValue, *ptr);
}
