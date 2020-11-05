#include <gtest/gtest.h>

#include "SharedPtr.hpp"

constexpr int initValue = 5;
constexpr int newValue = 10;

struct SharedPtrTest : public ::testing::Test {
    SharedPtrTest()
        : testSharedPtr(new int{initValue}) {}

    cs::SharedPtr<int> testSharedPtr;
};

TEST_F(SharedPtrTest, ShouldDereferenceSharedPtr) {
    ASSERT_EQ(*testSharedPtr, initValue);
}

TEST_F(SharedPtrTest, ShouldGetReturnPtrValue) {
    auto getPtr = testSharedPtr.get();

    ASSERT_EQ(*getPtr, *testSharedPtr);
}

TEST_F(SharedPtrTest, ShouldUninitializedSharedPtrBeNullPtr) {
    cs::SharedPtr<int> SharedNullPtr{};

    ASSERT_EQ(SharedNullPtr.get(), nullptr);
}

TEST_F(SharedPtrTest, ShouldResetSharedPtr) {
    int* tempPtr = new int{newValue};
    testSharedPtr.reset(tempPtr);

    ASSERT_EQ(*testSharedPtr, newValue);
}

TEST_F(SharedPtrTest, ShouldResetSharedPtrWithNoArgument) {
    testSharedPtr.reset();

    ASSERT_EQ(testSharedPtr.get(), nullptr);
}

TEST_F(SharedPtrTest, ShouldUseBoolOperator) {
    ASSERT_TRUE(testSharedPtr);

    testSharedPtr.reset();

    ASSERT_FALSE(testSharedPtr);
}

TEST_F(SharedPtrTest, ShouldMoveSharedPtr) {
    auto initTestSharedCounts = testSharedPtr.use_count();
    auto tempPtr(std::move(testSharedPtr));
    auto tempPtrSharedCountsAfterMove = tempPtr.use_count();

    ASSERT_EQ(*tempPtr, initValue);
    ASSERT_FALSE(testSharedPtr);
    ASSERT_EQ(initTestSharedCounts, tempPtrSharedCountsAfterMove);
    ASSERT_EQ(1, tempPtrSharedCountsAfterMove);
}

TEST_F(SharedPtrTest, ShouldMoveSharedPtrToPointerThatAlreadyHoldsAnObject) {
    auto initTestSharedCounts = testSharedPtr.use_count();
    cs::SharedPtr<int> tempPtr(new int{newValue});
    tempPtr = std::move(testSharedPtr);
    auto tempPtrSharedCountsAfterMove = tempPtr.use_count();

    ASSERT_EQ(*tempPtr, initValue);
    ASSERT_EQ(testSharedPtr.get(), nullptr);
    ASSERT_EQ(initTestSharedCounts, tempPtrSharedCountsAfterMove);
    ASSERT_EQ(1, tempPtrSharedCountsAfterMove);
}

TEST_F(SharedPtrTest, ShouldCopySharedPtrAndCalculateUseCountWhenCopyingSharedPtr) {
    auto initTestPtrSharedCounts = testSharedPtr.use_count();
    auto tempPtr(testSharedPtr);
    auto testPtrSharedCountsAfterFirstCopy = testSharedPtr.use_count();
    auto tempPtr2 = testSharedPtr;
    auto testPtrSharedCountsAfterSecondCopy = testSharedPtr.use_count();

    ASSERT_EQ(initTestPtrSharedCounts + 1, testPtrSharedCountsAfterFirstCopy);
    ASSERT_EQ(initTestPtrSharedCounts + 2, testPtrSharedCountsAfterSecondCopy);
    ASSERT_EQ(*tempPtr, initValue);
    ASSERT_EQ(*tempPtr2, initValue);
    ASSERT_EQ(*testSharedPtr, initValue);
    ASSERT_TRUE(testSharedPtr);
}

TEST_F(SharedPtrTest, ShouldCalculateUseCountWhenMoveingSharedPtr) {
    auto initTestSharedCounts = testSharedPtr.use_count();
    auto tempPtr(std::move(testSharedPtr));
    auto tempPtrSharedCountsAfterMove = tempPtr.use_count();

    ASSERT_EQ(initTestSharedCounts, tempPtrSharedCountsAfterMove);
}
