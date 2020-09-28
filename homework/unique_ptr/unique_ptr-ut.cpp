#include <gtest/gtest.h>

#include "unique_ptr.hpp"

constexpr int value = 77;
constexpr int newValue = 99;

class unique_ptrTest : public ::testing::Test {
protected:
    unique_ptrTest() : testUniquePtr(new int{value}) {}
    unique_ptr<int> testUniquePtr;
};

TEST_F(unique_ptrTest, UniquePtrCanDereferencePointer) {
    ASSERT_EQ(*testUniquePtr, value);
}

TEST_F(unique_ptrTest, UniquePtrCanChangeValue) {
    *testUniquePtr = newValue;
    ASSERT_EQ(*testUniquePtr, newValue);
}

TEST_F(unique_ptrTest, UniquePtrCanMovePointer) {
    unique_ptr<int> newTestUniquePtr = std::move(testUniquePtr);
    ASSERT_EQ(*newTestUniquePtr, value);
    ASSERT_EQ(testUniquePtr.get(), nullptr);
}

TEST_F(unique_ptrTest, UniquePtrCanUseReset) {
    testUniquePtr.reset(new int{newValue});
    ASSERT_EQ(*testUniquePtr, newValue);
}

TEST_F(unique_ptrTest, UniquePtrCanUseResetWithoutValue) {
    testUniquePtr.reset();
    ASSERT_EQ(testUniquePtr.get(), nullptr);
}

TEST_F(unique_ptrTest, UniquePtrCanUseGet) {
    auto ptr = testUniquePtr.get();
    ASSERT_EQ(*testUniquePtr, *ptr);
}

TEST_F(unique_ptrTest, UniquePtrCanUseRelease) {
    auto ptr = testUniquePtr.release();
    ASSERT_EQ(*ptr, value);
    ASSERT_EQ(testUniquePtr.get(), nullptr);
    delete ptr;
}
