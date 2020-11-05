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

TEST(MakeSharedPtrTest, ShouldMakeSharedPtrToInt) {
    cs::SharedPtr<int> shPtr(new int{intTestVal});
    auto makeShPtr = cs::makeShared<int>(intTestVal);
    ASSERT_EQ(*shPtr, *makeShPtr);
}

TEST(MakeSharedPtrTest, ShouldMakeSharedPtrToTestStruct) {
    auto makeShPtr = cs::makeShared<testStruct>(intTestVal, doubleTestVal);
    ASSERT_EQ(makeShPtr->intValue_, intTestVal);
    ASSERT_EQ(makeShPtr->doubleValue_, doubleTestVal);
}
