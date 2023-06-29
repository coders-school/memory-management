#include <gtest/gtest.h>
#include "shared_ptr.hpp"
template class my::shared_ptr<int>;

struct TestObject {
    int value_;
    TestObject(int value)
        : value_(value) {}
    TestObject(){};
    int multiplyValueByTwo() {
        return value_ *= 2;
    }
};

TEST(shared_ptrTest, ArrowOperatorTestNumberEqualsForty) {
    my::shared_ptr<TestObject> shared_ptr(new TestObject{20});
    auto expected = 40;

    EXPECT_EQ(expected, shared_ptr->multiplyValueByTwo());
}

TEST(shared_ptrTest, ArrowOperatorTestNumberEqualsZero) {
    my::shared_ptr<TestObject> shared_ptr(new TestObject{0});
    auto expected = 0;

    EXPECT_EQ(expected, shared_ptr->multiplyValueByTwo());
}

TEST(shared_ptrTest, DereferenceOperatorTestNumberEqualsForty) {
    my::shared_ptr<TestObject> shared_ptr(new TestObject(20));
    TestObject& dereferencedObj = *shared_ptr;
    auto result = dereferencedObj.multiplyValueByTwo();
    auto expected = 40;

    EXPECT_EQ(expected, result);
}

TEST(shared_ptrTest, DereferenceOperatorTestNumberEqualsZero) {
    my::shared_ptr<TestObject> shared_ptr(new TestObject(0));
    TestObject& dereferencedObj = *shared_ptr;
    auto result = dereferencedObj.multiplyValueByTwo();
    auto expected = 0;

    EXPECT_EQ(expected, result);
}

TEST(shared_ptrTest, FunctionGetExpectedNotNullTest) {
    my::shared_ptr<TestObject> shared_ptr(new TestObject(20));
    TestObject* rawPtr = shared_ptr.get();
    auto expected = nullptr;

    EXPECT_NE(expected, rawPtr);
}

TEST(shared_ptrTest, FunctionGetExpectedFortyTest) {
    my::shared_ptr<TestObject> shared_ptr(new TestObject(20));
    TestObject* rawPtr = shared_ptr.get();
    auto expected = 40;
    auto result = rawPtr->multiplyValueByTwo();

    EXPECT_EQ(expected, result);
}

TEST(shared_ptrTest, FunctionGetExpectedZeroTest) {
    my::shared_ptr<TestObject> shared_ptr(new TestObject(0));
    TestObject* rawPtr = shared_ptr.get();
    auto expected = 0;
    auto result = rawPtr->multiplyValueByTwo();

    EXPECT_EQ(expected, result);
}

TEST(shared_ptrTest, DefaultConstructorTest) {
    my::shared_ptr<TestObject> shared_ptr;
    auto value = shared_ptr.get();
    auto expected = nullptr;

    EXPECT_EQ(expected, value);
}

TEST(shared_ptrTest, MoveConstructorOriginalEqualsNullTest) {
    my::shared_ptr<TestObject> originalPtr(new TestObject(20));
    my::shared_ptr<TestObject> movedPtr(std::move(originalPtr));
    auto nullValue = originalPtr.get();
    auto expected = nullptr;

    EXPECT_EQ(expected, nullValue);
}

TEST(shared_ptrTest, MoveConstructorMovedNotEqualsNullTest) {
    my::shared_ptr<TestObject> originalPtr(new TestObject(20));
    my::shared_ptr<TestObject> movedPtr(std::move(originalPtr));
    auto nullValue = movedPtr.get();
    auto notExpected = nullptr;

    EXPECT_NE(notExpected, nullValue);
}

TEST(shared_ptrTest, MoveConstructorMovedEqualsZero) {
    my::shared_ptr<int> originalPtr(new int{0});
    my::shared_ptr<int> movedPtr(std::move(originalPtr));
    auto nullValue = movedPtr.get();
    auto notExpected = nullptr;

    EXPECT_NE(notExpected, nullValue);
}

TEST(shared_ptrTest, MoveConstructorMovedEqualsOneAndAHalf) {
    my::shared_ptr<double> originalPtr(new double{1.5});
    my::shared_ptr<double> movedPtr(std::move(originalPtr));
    auto nullValue = movedPtr.get();
    auto notExpected = nullptr;

    EXPECT_NE(notExpected, nullValue);
}

TEST(shared_ptrTest, CopyConstructorCounterEqualsTwoTest) {
    my::shared_ptr<TestObject> ptr(new TestObject(20));
    auto ptr2(ptr);
    auto ptrCounter = ptr.use_count();
    auto expected = 2;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyConstructorCounterEqualsTwoTestOfIntegers) {
    my::shared_ptr<int> ptr(new int{0});
    auto ptr2(ptr);
    auto ptrCounter = ptr.use_count();
    auto expected = 2;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyConstructorCounterEqualsTwoTestOfDouble) {
    my::shared_ptr<double> ptr(new double{1.6});
    auto ptr2(ptr);
    auto ptrCounter = ptr.use_count();
    auto expected = 2;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyConstructorCounterEqualsThreeTest) {
    my::shared_ptr<TestObject> ptr(new TestObject(20));
    auto ptr2(ptr);
    auto ptr3(ptr);
    auto ptrCounter = ptr.use_count();
    auto expected = 3;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyConstructorCounterEqualsThreeTestOfIntegers) {
    my::shared_ptr<int> ptr(new int{0});
    auto ptr2(ptr);
    auto ptr3(ptr);
    auto ptrCounter = ptr.use_count();
    auto expected = 3;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyConstructorCounterEqualsThreeTestOfDoubles) {
    my::shared_ptr<double> ptr(new double{1.7});
    auto ptr2(ptr);
    auto ptr3(ptr);
    auto ptrCounter = ptr.use_count();
    auto expected = 3;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyAssignmentTwoDefultConstructorTest) {
    my::shared_ptr<TestObject> ptr;
    my::shared_ptr<TestObject> ptr2;
    ptr2 = ptr;
    auto ptrCounter = ptr.use_count();
    auto expected = 0;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyAssignmentFourDefultConstructorTest) {
    my::shared_ptr<TestObject> ptr;
    my::shared_ptr<TestObject> ptr2;
    my::shared_ptr<TestObject> ptr3;
    my::shared_ptr<TestObject> ptr4;
    ptr2 = ptr;
    ptr3 = ptr;
    ptr4 = ptr;
    auto ptrCounter = ptr.use_count();
    auto expected = 0;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyAssignmentThreerDefultConstructorAssignesToOneTest) {
    my::shared_ptr<TestObject> ptr;
    my::shared_ptr<TestObject> ptr2;
    my::shared_ptr<TestObject> ptr3;
    ptr3 = ptr2 = ptr;
    auto ptrCounter = ptr.use_count();
    auto expected = 0;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyAssignmentFourDefultConstructorAssignesToOneTest) {
    my::shared_ptr<TestObject> ptr;
    my::shared_ptr<TestObject> ptr2;
    my::shared_ptr<TestObject> ptr3;
    my::shared_ptr<TestObject> ptr4;
    ptr4 = ptr3 = ptr2 = ptr;
    auto ptrCounter = ptr.use_count();
    auto expected = 0;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyAssignmentFourDefultIntegerConstructorTest) {
    my::shared_ptr<double> ptr;
    my::shared_ptr<double> ptr2;
    my::shared_ptr<double> ptr3;
    my::shared_ptr<double> ptr4;
    ptr2 = ptr;
    ptr3 = ptr;
    ptr4 = ptr;
    auto ptrCounter = ptr.use_count();
    auto expected = 0;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyAssignmentCounterEqualsTwoTest) {
    my::shared_ptr<TestObject> ptr(new TestObject(20));
    my::shared_ptr<TestObject> ptr2(new TestObject(20));
    ptr2 = ptr;
    auto ptrCounter = ptr.use_count();
    auto expected = 2;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyAssignmentCounterEqualsFiveTestObjectsTest) {
    my::shared_ptr<TestObject> ptr(new TestObject(20));
    my::shared_ptr<TestObject> ptr2(new TestObject(30));
    my::shared_ptr<TestObject> ptr3(new TestObject(40));
    my::shared_ptr<TestObject> ptr4(new TestObject(50));
    my::shared_ptr<TestObject> ptr5(new TestObject(60));
    ptr2 = ptr;
    ptr3 = ptr;
    ptr4 = ptr;
    ptr5 = ptr;
    auto ptrCounter = ptr.use_count();
    auto expected = 5;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyAssignmentAssignToOneCounterEqualsFiveTestObjectsTest) {
    my::shared_ptr<TestObject> ptr(new TestObject(20));
    my::shared_ptr<TestObject> ptr2(new TestObject(30));
    my::shared_ptr<TestObject> ptr3(new TestObject(40));
    my::shared_ptr<TestObject> ptr4(new TestObject(50));
    my::shared_ptr<TestObject> ptr5(new TestObject(60));
    ptr5 = ptr4 = ptr3 = ptr2 = ptr;
    auto ptrCounter = ptr.use_count();
    auto expected = 5;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyAssignmentCounterEqualsFiveIntegersTest) {
    my::shared_ptr<int> ptr(new int{0});
    my::shared_ptr<int> ptr2(new int{0});
    my::shared_ptr<int> ptr3(new int{0});
    my::shared_ptr<int> ptr4(new int{0});
    my::shared_ptr<int> ptr5(new int{0});
    ptr2 = ptr;
    ptr3 = ptr;
    ptr4 = ptr;
    ptr5 = ptr;
    auto ptrCounter = ptr.use_count();
    auto expected = 5;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyAssignmentCounterEqualsThreeTest) {
    my::shared_ptr<TestObject> ptr(new TestObject(20));
    my::shared_ptr<TestObject> ptr2(new TestObject(20));
    my::shared_ptr<TestObject> ptr3(new TestObject(20));
    ptr2 = ptr;
    ptr3 = ptr;
    auto ptrCounter = ptr.use_count();
    auto expected = 3;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, MoveOperatorMoveOriginalPtrEqualsNullTest) {
    my::shared_ptr<TestObject> originalPtr(new TestObject(20));
    auto newPtr = std::move(originalPtr);
    auto nullValue = originalPtr.get();
    auto expected = nullptr;

    EXPECT_EQ(expected, nullValue);
}

TEST(shared_ptrTest, MoveOperatorMoveNewPtrNotEqualsNullTest) {
    my::shared_ptr<TestObject> originalPtr(new TestObject(20));
    auto newPtr = std::move(originalPtr);
    auto notNullValue = newPtr.get();
    auto notExpected = nullptr;

    EXPECT_NE(notExpected, notNullValue);
}

TEST(shared_ptrTest, MoveOperatorMoveNewZeroPtrNotEqualsNullTest) {
    my::shared_ptr<int> originalPtr(new int{0});
    auto newPtr = std::move(originalPtr);
    auto notNullValue = newPtr.get();
    auto notExpected = nullptr;

    EXPECT_NE(notExpected, notNullValue);
}

TEST(shared_ptrTest, BoolOperatorReturnsFalse) {
    my::shared_ptr<TestObject> originalPtr;
    bool isNullValue = true;
    if (originalPtr) {
        isNullValue = false;
    }
    auto expected = true;

    EXPECT_EQ(expected, isNullValue);
}

TEST(shared_ptrTest, BoolOperatorReturnsFalseOfZero) {
    my::shared_ptr<TestObject> originalPtr(0);
    bool isNullValue = true;
    if (originalPtr) {
        isNullValue = false;
    }
    auto expected = true;

    EXPECT_EQ(expected, isNullValue);
}

TEST(shared_ptrTest, BoolOperatorReturnsTrueOfTwenty) {
    my::shared_ptr<TestObject> originalPtr(new TestObject(20));
    bool isNullValue = true;
    if (originalPtr) {
        isNullValue = false;
    }
    auto expected = false;

    EXPECT_EQ(expected, isNullValue);
}

TEST(shared_ptrTest, BoolOperatorReturnsTrueOfZero) {
    my::shared_ptr<int> originalPtr(new int{0});
    bool isNullValue = true;
    if (originalPtr) {
        isNullValue = false;
    }
    auto expected = false;

    EXPECT_EQ(expected, isNullValue);
}

TEST(shared_ptrTest, FunctionResetSharedPtrEqualsNull) {
    my::shared_ptr<TestObject> shared_ptr(new TestObject(20));
    shared_ptr.reset(nullptr);
    auto value = shared_ptr.get();
    auto expected = nullptr;

    EXPECT_EQ(value, expected);
}

TEST(shared_ptrTest, FunctionResetSharedPtrNotEqualsZero) {
    my::shared_ptr<int> shared_ptr(new int{10});
    shared_ptr.reset(new int{0});
    auto value = shared_ptr.get();
    auto notExpected = nullptr;

    EXPECT_NE(value, notExpected);
}

TEST(shared_ptrTest, FunctionResetSharedPtrEqualsZero) {
    my::shared_ptr<TestObject> shared_ptr(new TestObject(20));
    shared_ptr.reset(new TestObject(0));
    auto value = shared_ptr->value_;
    auto expected = 0;

    EXPECT_EQ(value, expected);
}

TEST(shared_ptrTest, FunctionResetSharedPtrEqualsNullptr) {
    my::shared_ptr<TestObject> shared_ptr(new TestObject(20));
    shared_ptr.reset();
    auto value = shared_ptr.get();
    auto expected = nullptr;

    EXPECT_EQ(value, expected);
}
