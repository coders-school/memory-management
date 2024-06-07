#include <gtest/gtest.h>

#include "MakeShared.hpp"
#include "SharedPtr.hpp"

constexpr int intTestVal = 15;
constexpr int doubleTestVal = 1.5;

struct testStruct {
    testStruct(int first, double second)
        : intValue_(first), doubleValue_(second) {}

    int intValue_;
    double doubleValue_;
};

void expectMakePtrValuesEqualToTestValues(
    cs::SharedPtr<testStruct>& tempPtr,
    int intTestVal,
    double doubleTestVal) {
    ASSERT_EQ(tempPtr->intValue_, intTestVal);
    ASSERT_EQ(tempPtr->doubleValue_, doubleTestVal);
}

TEST(MakeSharedPtrTest, ShouldMakeSharedPtrToInt) {
    cs::SharedPtr<int> shPtr(new int{intTestVal});
    auto makeShPtr = cs::makeShared<int>(intTestVal);
    ASSERT_EQ(*shPtr, *makeShPtr);
}

TEST(MakeSharedPtrTest, ShouldMakeSharedPtrToTestStruct) {
    auto makeShPtr = cs::makeShared<testStruct>(intTestVal, doubleTestVal);

    expectMakePtrValuesEqualToTestValues(makeShPtr, intTestVal, doubleTestVal);
}

TEST(MakeSharedPtrTest, ShouldMoveMakeSharedPtr) {
    auto makeShPtr = cs::makeShared<testStruct>(intTestVal, doubleTestVal);

    auto initTestSharedCounts = makeShPtr.use_count();
    auto tempPtr(std::move(makeShPtr));
    auto tempPtrSharedCountsAfterMove = tempPtr.use_count();

    expectMakePtrValuesEqualToTestValues(tempPtr, intTestVal, doubleTestVal);

    ASSERT_FALSE(makeShPtr);
    ASSERT_EQ(initTestSharedCounts, tempPtrSharedCountsAfterMove);
    ASSERT_EQ(1, tempPtrSharedCountsAfterMove);
}

TEST(MakeSharedPtrTest, ShouldCopyMakeSharedPtrAndCalculateUseCount) {
    auto makeShPtr = cs::makeShared<testStruct>(intTestVal, doubleTestVal);

    auto initTestPtrSharedCounts = makeShPtr.use_count();
    auto tempPtr(makeShPtr);
    auto testPtrSharedCountsAfterFirstCopy = makeShPtr.use_count();
    auto tempPtr2 = makeShPtr;
    auto testPtrSharedCountsAfterSecondCopy = makeShPtr.use_count();

    ASSERT_EQ(initTestPtrSharedCounts + 1, testPtrSharedCountsAfterFirstCopy);
    ASSERT_EQ(initTestPtrSharedCounts + 2, testPtrSharedCountsAfterSecondCopy);
    ASSERT_TRUE(makeShPtr);

    expectMakePtrValuesEqualToTestValues(tempPtr, intTestVal, doubleTestVal);
    expectMakePtrValuesEqualToTestValues(tempPtr2, intTestVal, doubleTestVal);
    expectMakePtrValuesEqualToTestValues(makeShPtr, intTestVal, doubleTestVal);
}