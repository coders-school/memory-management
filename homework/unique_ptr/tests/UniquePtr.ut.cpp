#include <gtest/gtest.h>
#include "UniquePtr.hpp"

constexpr int FirstPointerValue = 9;
constexpr int SecondVectorValue = 99;
constexpr int ArrowValueTest = 5;
constexpr int MoveInitialValue = 12;

class ArrowTest {
public:
    ArrowTest(int value)
        : value_{value} {}
    auto arrowGetTest() {
        return value_;
    }

private:
    int value_;
};

class MoveUniqueTestClass : public testing::Test {
public:
    MoveUniqueTestClass()
        : uniquePtrTest_(new int{MoveInitialValue}) {}
    UniquePtr<int> uniquePtrTest_;
};

TEST(UniquePtrTest, UniquePointerDereferenceOperatorShouldReturnValue) {
    UniquePtr<int> ptr{new int{FirstPointerValue}};
    ASSERT_EQ(FirstPointerValue, *ptr);
}

TEST(UniquePtrTest, UniquePtrArrowOperatorShouldReturnFunctionValue) {
    UniquePtr<ArrowTest> ptr = new ArrowTest(ArrowValueTest);
    ASSERT_EQ(ptr->arrowGetTest(), ArrowValueTest);
}

TEST(UniquePtrTest, UniquePtrAfterResetShouldContainNewValue) {
    UniquePtr<int> ptr{new int{FirstPointerValue}};
    ptr.reset(new int{SecondVectorValue});
    ASSERT_EQ(SecondVectorValue, *ptr);
}

TEST(UniquePtrTest, UniquePtrGetShouldGiveUsValueOfPointer) {
    UniquePtr<int> ptr{new int{FirstPointerValue}};
    auto newPtr = ptr.get();
    ASSERT_EQ(FirstPointerValue, *newPtr);
}

TEST(UniquePtrTest, UniquePtrAfterReleaseShouldBeNullptr) {
    UniquePtr<int> ptr{new int{FirstPointerValue}};
    int* released = ptr.release();
    ASSERT_EQ(ptr.get(), nullptr);
    ASSERT_EQ(*released, FirstPointerValue);
    delete released;
}

TEST(UniquePtrTest, DereferenceOfNullptrShouldReturnException) {
    UniquePtr<int> ptr{nullptr};
    ASSERT_THROW(*ptr, NullptrDereferenceError);
}

TEST_F(MoveUniqueTestClass, MoveConstructorTest) {
    UniquePtr<int> ptr{std::move(uniquePtrTest_)};
    ASSERT_EQ(uniquePtrTest_.get(), nullptr);
    ASSERT_EQ(MoveInitialValue, *ptr);
}

TEST_F(MoveUniqueTestClass, MoveAssignmentTest) {
    UniquePtr<int> ptr{new int{SecondVectorValue}};
    ptr = std::move(uniquePtrTest_);
    ASSERT_EQ(uniquePtrTest_.get(), nullptr);
    ASSERT_EQ(MoveInitialValue, *ptr);
}
