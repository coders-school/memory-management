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

TEST(unique_ptrTest, ArrowOperatorTest) {
    my::unique_ptr<TestObject> unique_ptr(new TestObject{20});
    auto expected = 40;

    EXPECT_EQ(expected, unique_ptr->multiplyValueByTwo());
}

TEST(unique_ptrTest, DereferenceOperatorTest) {
    my::unique_ptr<TestObject> unique_ptr(new TestObject(20));
    TestObject& dereferencedObj = *unique_ptr;
    auto result = dereferencedObj.multiplyValueByTwo();
    auto expected = 40;

    EXPECT_EQ(expected, result);
}

TEST(unique_ptrTest, FunctionGetExpectedNotNullTest) {
    my::unique_ptr<TestObject> unique_ptr(new TestObject(20));
    TestObject* rawPtr = unique_ptr.get();
    auto expected = nullptr;

    EXPECT_NE(expected, rawPtr);
}

TEST(unique_ptrTest, FunctionGetExpectedValueTest) {
    my::unique_ptr<TestObject> unique_ptr(new TestObject(20));
    TestObject* rawPtr = unique_ptr.get();
    auto expected = 40;
    auto result = rawPtr->multiplyValueByTwo();

    EXPECT_EQ(expected, result);
}

TEST(unique_ptrTest, DefaultConstructorTest) {
    my::unique_ptr<TestObject> unique_ptr;
    auto value = unique_ptr.get();
    auto expected = nullptr;

    EXPECT_EQ(expected, value);
}

TEST(unique_ptrTest, FunctionResetUniquePtr1EqualsUniquePtr2) {
    my::unique_ptr<TestObject> unique_ptr1(new TestObject(20));
    unique_ptr1.reset(new TestObject(30));
    auto value = unique_ptr1->value_;
    auto expected = 30;

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
