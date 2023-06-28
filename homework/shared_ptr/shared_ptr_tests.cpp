#include <gtest/gtest.h>
#include "shared_ptr.hpp"

struct TestObject
{
  int value_;
  TestObject(int value) : value_(value){}
  TestObject(){};
  int multiplyValueByTwo()
  {
    return value_ *= 2;
  }
};

TEST(shared_ptrTest, ArrowOperatorTest)
{
  my::shared_ptr<TestObject> shared_ptr(new TestObject{20});
  auto expected = 40;

  EXPECT_EQ(expected, shared_ptr->multiplyValueByTwo());
}

TEST(shared_ptrTest, DereferenceOperatorTest)
{
  my::shared_ptr<TestObject> shared_ptr(new TestObject(20));
  TestObject& dereferencedObj = *shared_ptr;
  auto result = dereferencedObj.multiplyValueByTwo();
  auto expected = 40;

  EXPECT_EQ(expected, result);
}

TEST(shared_ptrTest, FunctionGetExpectedNotNullTest)
{
  my::shared_ptr<TestObject> shared_ptr(new TestObject(20));
  TestObject* rawPtr = shared_ptr.get();
  auto expected = nullptr;

  EXPECT_NE(expected, rawPtr);
}

TEST(shared_ptrTest, FunctionGetExpectedValueTest)
{
  my::shared_ptr<TestObject> shared_ptr(new TestObject(20));
  TestObject* rawPtr = shared_ptr.get();
  auto expected = 40;
  auto result = rawPtr->multiplyValueByTwo();

  EXPECT_EQ(expected, result);
}

TEST(shared_ptrTest, DefaultConstructorTest)
{
  my::shared_ptr<TestObject> shared_ptr;
  auto value = shared_ptr.get();
  auto expected = nullptr;

  EXPECT_EQ(expected, value);
}

TEST(shared_ptrTest, MoveConstructorOriginalEqualsNullTest) 
{
  my::shared_ptr<TestObject> originalPtr(new TestObject(20));
  my::shared_ptr<TestObject> movedPtr(std::move(originalPtr));
  auto nullValue = originalPtr.get();
  auto expected = nullptr;

  EXPECT_EQ(expected, nullValue);
}

TEST(shared_ptrTest, MoveConstructorMovedNotEqualsNullTest) 
{
  my::shared_ptr<TestObject> originalPtr(new TestObject(20));
  my::shared_ptr<TestObject> movedPtr(std::move(originalPtr));
  auto nullValue = movedPtr.get();
  auto notExpected = nullptr;

  EXPECT_NE(notExpected, nullValue);
}

TEST(shared_ptrTest, CopyConstructorCounterEqualsTwoTest) 
{
  my::shared_ptr<TestObject> ptr(new TestObject(20));
  auto ptr2(ptr);
  auto ptrCounter = ptr.use_count();
  auto expected = 2;

  EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyConstructorCounterEqualsThreeTest) 
{
  my::shared_ptr<TestObject> ptr(new TestObject(20));
  auto ptr2(ptr);
  auto ptr3(ptr);
  auto ptrCounter = ptr.use_count();
  auto expected = 3;

  EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyAssignmentDefultConstructorTest) 
{
  my::shared_ptr<TestObject> ptr;
  my::shared_ptr<TestObject> ptr2;
  ptr2 = ptr;
  auto ptrCounter = ptr.use_count();
  auto expected = 0;

  EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyAssignmentCounterEqualsTwoTest) 
{
  my::shared_ptr<TestObject> ptr(new TestObject(20));
  my::shared_ptr<TestObject> ptr2(new TestObject(20));
  ptr2 = ptr;
  auto ptrCounter = ptr.use_count();
  auto expected = 2;

  EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, CopyAssignmentCounterEqualsThreeTest) 
{
  my::shared_ptr<TestObject> ptr(new TestObject(20));
  my::shared_ptr<TestObject> ptr2(new TestObject(20));
  my::shared_ptr<TestObject> ptr3(new TestObject(20));
  ptr2 = ptr;
  ptr3 = ptr;
  auto ptrCounter = ptr.use_count();
  auto expected = 3;

  EXPECT_EQ(expected, ptrCounter);
}

TEST(shared_ptrTest, MoveOperatorMoveOriginalPtrEqualsNullTest) 
{
  my::shared_ptr<TestObject> originalPtr(new TestObject(20));
  auto newPtr = std::move(originalPtr);
  auto nullValue = originalPtr.get();
  auto expected = nullptr;

  EXPECT_EQ(expected, nullValue);
}

TEST(shared_ptrTest, MoveOperatorMoveNewPtrNotEqualsNullTest) 
{
  my::shared_ptr<TestObject> originalPtr(new TestObject(20));
  auto newPtr = std::move(originalPtr);
  auto notNullValue = newPtr.get();
  auto notExpected = nullptr;

  EXPECT_NE(notExpected, notNullValue);
}

TEST(shared_ptrTest, BoolOperatorReturnsFalse) 
{
  my::shared_ptr<TestObject> originalPtr;
  bool isNullValue = true;
  if(originalPtr)
  {
    isNullValue = false;
  }
  auto expected = true;

  EXPECT_EQ(expected, isNullValue);
}

TEST(shared_ptrTest, BoolOperatorReturnsTrue) 
{
  my::shared_ptr<TestObject> originalPtr(new TestObject(20));
  bool isNullValue = true;
  if(originalPtr)
  {
    isNullValue = false;
  }
  auto expected = false;

  EXPECT_EQ(expected, isNullValue);
}

TEST(shared_ptrTest, FunctionResetOnePtrNotNullEqualsNull)
{
  my::shared_ptr<TestObject> shared_ptr(new TestObject(20));
  shared_ptr.reset();
  auto nullValue = shared_ptr.get();
  auto expected = nullptr;

  EXPECT_EQ(expected, nullValue);
}

TEST(shared_ptrTest, FunctionResetOnePtrNullEqualsNull)
{
  my::shared_ptr<TestObject> shared_ptr;
  shared_ptr.reset();
  auto nullValue = shared_ptr.get();
  auto expected = nullptr;

  EXPECT_EQ(expected, nullValue);
}