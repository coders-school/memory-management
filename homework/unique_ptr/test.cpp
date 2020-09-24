#include <gtest/gtest.h>
#include <string>
#include "UniquePointer.hpp"

constexpr int testValue1 = 20;
constexpr int testValue2 = 40;

struct TestUniquePtr : ::testing::Test {
    TestUniquePtr() : uPtr(new int{testValue1}) {}
    UniquePointer<int> uPtr;
};

TEST_F(TestUniquePtr, TestOfConstructor) {
    ASSERT_EQ(testValue1, *uPtr);
}

TEST_F(TestUniquePtr, TestOfGetMethod) {
    auto ptr = uPtr.get();
    ASSERT_EQ(*ptr, testValue1);
}

TEST_F(TestUniquePtr, TestOfResetMethod) {
    uPtr.reset(new int{testValue2});
    ASSERT_EQ(testValue2, *uPtr);
}

TEST_F(TestUniquePtr, TestOfReleaseMethod) {
    UniquePointer<int> ptr(new int(testValue2));
    auto newPtr = ptr.release();
    ASSERT_EQ(*newPtr, testValue2);
    ASSERT_EQ(ptr.get(), nullptr);
    delete newPtr;
}

TEST_F(TestUniquePtr, TestOfNullPtrException) {
    UniquePointer<int> ptr{nullptr};
    ASSERT_THROW(*ptr, NullPtrException);
}

TEST_F(TestUniquePtr, TestOfMoveConstructor) {
    UniquePointer<int> ptr(std::move(uPtr));
    ASSERT_EQ(testValue1, *ptr);
}

TEST_F(TestUniquePtr, TestOfMoveAssignmentOperator) {
    UniquePointer<int> ptr{new int{testValue2}};
    UniquePointer<int> ptr2 = std::move(ptr);
    ASSERT_EQ(ptr.get(), nullptr);
    ASSERT_EQ(testValue2, *ptr2);
}

TEST_F(TestUniquePtr, TestOfArrowOperator) {
    std::string testString = "test";
    UniquePointer<std::string> ptr{new std::string(testString)};
    ASSERT_EQ(ptr->at(1), testString.at(1));
    ASSERT_EQ(ptr->at(2), testString.at(2));
}
