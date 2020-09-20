#include <gtest/gtest.h>

#include "UniquePtr.hpp"

constexpr int initValue = 5;
constexpr int newValue = 10;

struct UniquePtrTest : public ::testing::Test {
    UniquePtrTest()
        : testPtr(new int{initValue}) {}

    UniquePtr<int> testPtr;
};

TEST_F(UniquePtrTest, ShouldThrowDereferenceNullPtrError) {
    testPtr.reset();
    ASSERT_EQ(testPtr.get(), nullptr);
    ASSERT_THROW(*testPtr, DereferenceNullPtrError);
}

TEST_F(UniquePtrTest, ShouldDereferenceUniquePtr) {
    ASSERT_EQ(*testPtr, initValue);
}

TEST_F(UniquePtrTest, ShouldGetReturnPtrValue) {
    auto getPtr = testPtr.get();
    ASSERT_EQ(*getPtr, *testPtr);
}

TEST_F(UniquePtrTest, ShouldUninitializedUniquePtrBeNullPtr) {
    UniquePtr<int> uniqueNullPtr{};
    ASSERT_EQ(uniqueNullPtr.get(), nullptr);
}

TEST_F(UniquePtrTest, ShouldReleaseUniquePtr) {
    auto tempPtr = testPtr.release();
    ASSERT_EQ(*tempPtr, initValue);
    ASSERT_EQ(testPtr.get(), nullptr);
    delete tempPtr;
}

TEST_F(UniquePtrTest, ShouldResetUniquePtr) {
    int* tempPtr = new int{newValue};
    testPtr.reset(tempPtr);
    ASSERT_EQ(*testPtr, newValue);
}

TEST_F(UniquePtrTest, ShouldResetUniquePtrWithNoArgument) {
    int* tempPtr = new int{newValue};
    testPtr.reset();
    ASSERT_EQ(testPtr.get(), nullptr);
}

TEST_F(UniquePtrTest, ShouldMoveUniquePtr) {
    auto tempPtr(std::move(testPtr));
    ASSERT_EQ(*tempPtr, initValue);
    ASSERT_EQ(testPtr.get(), nullptr);
}

TEST_F(UniquePtrTest, ShouldMoveUniquePtrToPointerThatAlreadyHoldsAnObject) {
    UniquePtr<int> tempPtr(new int{newValue});
    tempPtr = std::move(testPtr);
    ASSERT_EQ(*tempPtr, initValue);
    ASSERT_EQ(testPtr.get(), nullptr);
}
