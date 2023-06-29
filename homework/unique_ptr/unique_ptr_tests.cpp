#include <gtest/gtest.h>
#include "unique_ptr.hpp"

struct TestObject {
    int value_;
    TestObject(int value)
        : value_(value) {}
    TestObject(){};
    int multiplyValueByTwo() {
        return value_ *= 2;
    }
};

template class my::unique_ptr<TestObject>;

TEST(unique_ptrTest, ArrowOperatorToFunctionTest) {
    my::unique_ptr<TestObject> unique_ptr(new TestObject{20});
    auto expected = 40;
    auto value = unique_ptr->multiplyValueByTwo();

    EXPECT_EQ(expected, value);
}

TEST(unique_ptrTest, ArrowOperatorToFunctionMemberValueEqualsZeroTest) {
    my::unique_ptr<TestObject> unique_ptr(new TestObject{0});
    auto expected = 0;
    auto value = unique_ptr->multiplyValueByTwo();

    EXPECT_EQ(expected, value);
}

TEST(unique_ptrTest, ArrowOperatorToMemberValueTest) {
    my::unique_ptr<TestObject> unique_ptr(new TestObject{20});
    auto expected = 20;
    auto value = unique_ptr->value_;

    EXPECT_EQ(expected, value);
}

TEST(unique_ptrTest, DereferenceOperatorToMemberFunctionTest) {
    my::unique_ptr<TestObject> unique_ptr(new TestObject(20));
    TestObject& dereferencedObj = *unique_ptr;
    auto result = dereferencedObj.multiplyValueByTwo();
    auto expected = 40;

    EXPECT_EQ(expected, result);
}

TEST(unique_ptrTest, DereferenceOperatorToMemberFunctionEqualsZeroTest) {
    my::unique_ptr<TestObject> unique_ptr(new TestObject(0));
    TestObject& dereferencedObj = *unique_ptr;
    auto result = dereferencedObj.multiplyValueByTwo();
    auto expected = 0;

    EXPECT_EQ(expected, result);
}

TEST(unique_ptrTest, DereferenceOperatorToMemberValueTest) {
    my::unique_ptr<TestObject> unique_ptr(new TestObject(20));
    TestObject& dereferencedObj = *unique_ptr;
    auto result = dereferencedObj.value_;
    auto expected = 20;

    EXPECT_EQ(expected, result);
}

TEST(unique_ptrTest, FunctionGetExpectedNotNullTest) {
    my::unique_ptr<TestObject> unique_ptr(new TestObject(20));
    TestObject* rawPtr = unique_ptr.get();
    auto expected = nullptr;

    EXPECT_NE(expected, rawPtr);
}

TEST(unique_ptrTest, ArrowOperatorToStringFunctionTest) {
    my::unique_ptr<std::string> unique_ptr("string");
    auto expected = true;
    auto value = unique_ptr->compare("string");

    EXPECT_EQ(expected, value);
}
TEST(unique_ptrTest, FunctionGetExpectedValueTest) {
    my::unique_ptr<TestObject> unique_ptr(new TestObject(20));
    TestObject* rawPtr = unique_ptr.get();
    auto expected = 40;
    auto result = rawPtr->multiplyValueByTwo();

    EXPECT_EQ(expected, result);
}

TEST(unique_ptrTest, FunctionGetExpectedNullValueTest) {
    my::unique_ptr<TestObject> unique_ptr;
    TestObject* rawPtr = unique_ptr.get();
    auto expected = nullptr;

    EXPECT_EQ(expected, rawPtr);
}

TEST(unique_ptrTest, DefaultConstructorTest) {
    my::unique_ptr<TestObject> unique_ptr;
    auto value = unique_ptr.get();
    auto expected = nullptr;

    EXPECT_EQ(expected, value);
}

TEST(unique_ptrTest, FunctionResetUniquePtr1EqualsNewPtr) {
    my::unique_ptr<TestObject> unique_ptr1(new TestObject(20));
    unique_ptr1.reset(new TestObject(30));
    auto value = unique_ptr1->value_;
    auto expected = 30;

    EXPECT_EQ(value, expected);
}

TEST(unique_ptrTest, FunctionResetUniquePtr1EqualsNull) {
    my::unique_ptr<TestObject> unique_ptr1(new TestObject(20));
    unique_ptr1.reset(nullptr);
    auto value = unique_ptr1.get();
    auto expected = nullptr;

    EXPECT_EQ(value, expected);
}

TEST(unique_ptrTest, FunctionResetUniquePtr1NotEqualsZero) {
    my::unique_ptr<int> unique_ptr1(new int{10});
    unique_ptr1.reset(new int{0});
    auto value = unique_ptr1.get();
    auto notExpected = nullptr;

    EXPECT_NE(value, notExpected);
}

TEST(unique_ptrTest, FunctionResetUniquePtr1EqualsZero) {
    my::unique_ptr<TestObject> unique_ptr1(new TestObject(20));
    unique_ptr1.reset(new TestObject(0));
    auto value = unique_ptr1->value_;
    auto expected = 0;

    EXPECT_EQ(value, expected);
}

TEST(unique_ptrTest, MoveConstructorOriginalEqualsNullTest) {
    my::unique_ptr<TestObject> originalPtr(new TestObject(20));
    my::unique_ptr<TestObject> movedPtr(std::move(originalPtr));
    auto nullValue = originalPtr.get();
    auto expected = nullptr;

    EXPECT_EQ(expected, nullValue);
}

TEST(unique_ptrTest, MoveConstructorMovedNotEqualsNullTest) {
    my::unique_ptr<TestObject> originalPtr(new TestObject(20));
    my::unique_ptr<TestObject> movedPtr(std::move(originalPtr));
    auto nullValue = movedPtr.get();
    auto notExpected = nullptr;

    EXPECT_NE(notExpected, nullValue);
}

TEST(unique_ptrTest, MoveOperatorMoveOriginalPtrEqualsNullTest) {
    my::unique_ptr<TestObject> originalPtr(new TestObject(20));
    auto newPtr = std::move(originalPtr);
    auto nullValue = originalPtr.get();
    auto expected = nullptr;

    EXPECT_EQ(expected, nullValue);
}

TEST(unique_ptrTest, MoveOperatorMoveNewPtrNotEqualsNullTest) {
    my::unique_ptr<TestObject> originalPtr(new TestObject(20));
    auto newPtr = std::move(originalPtr);
    auto notNullValue = newPtr.get();
    auto notExpected = nullptr;

    EXPECT_NE(notExpected, notNullValue);
}

TEST(unique_ptrTest, FunctionReleaseOriginalPtrEqualsNullTest) {
    my::unique_ptr<TestObject> originalPtr(new TestObject(20));
    auto newPtr = originalPtr.release();
    auto expected = nullptr;
    auto nullValue = originalPtr.get();

    EXPECT_EQ(expected, nullValue);
    delete nullValue;
    delete newPtr;
}

TEST(unique_ptrTest, FunctionReleaseNewPtrNotEqualsNullTest) {
    my::unique_ptr<TestObject> originalPtr(new TestObject(20));
    auto newPtr = originalPtr.release();
    auto notExpected = nullptr;

    EXPECT_NE(notExpected, newPtr);
    delete newPtr;  // has to be deleted
}
