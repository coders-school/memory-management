#include <gtest/gtest.h>
#include "my_unique_ptr.hpp"

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

TEST(MyUniquePtrTest, ArrowOperatorTest)
{
  MyUniquePtr<TestObject> myUniquePtr(new TestObject{20});
  auto expected = 40;

  EXPECT_EQ(expected, myUniquePtr->multiplyValueByTwo());
}

TEST(MyUniquePtrTest, DereferenceOperatorTest)
{
  MyUniquePtr<TestObject> myUniquePtr(new TestObject(20));
  TestObject& dereferencedObj = *myUniquePtr;
  auto result = dereferencedObj.multiplyValueByTwo();
  auto expected = 40;

  EXPECT_EQ(expected, result);
}

TEST(MyUniquePtrTest, FunctionGetExpectedNotNullTest)
{
  MyUniquePtr<TestObject> myUniquePtr(new TestObject(20));
  TestObject* rawPtr = myUniquePtr.get();
  auto expected = nullptr;

  EXPECT_NE(expected, rawPtr);
}

TEST(MyUniquePtrTest, FunctionGetExpectedValueTest)
{
  MyUniquePtr<TestObject> myUniquePtr(new TestObject(20));
  TestObject* rawPtr = myUniquePtr.get();
  auto expected = 40;
  auto result = rawPtr->multiplyValueByTwo();

  EXPECT_EQ(expected, result);
}

TEST(MyUniquePtrTest, DefaultConstructorTest)
{
  MyUniquePtr<TestObject> myUniquePtr;
  auto value = myUniquePtr.get();
  auto expected = nullptr;

  EXPECT_EQ(expected, value);
}

TEST(MyUniquePtrTest, FunctionResetNotNullNotEqualsNull)
{
  MyUniquePtr<TestObject> myUniquePtr(new TestObject(20));
  auto notNullValue = myUniquePtr.get();
  myUniquePtr.reset();
  auto nullValue = myUniquePtr.get();

  EXPECT_NE(notNullValue, nullValue);
}

TEST(MyUniquePtrTest, FunctionResetNotNullEqualsNull)
{
  MyUniquePtr<TestObject> myUniquePtr(new TestObject(20));
  myUniquePtr.reset();
  auto nullValue = myUniquePtr.get();
  auto expected = nullptr;

  EXPECT_EQ(expected, nullValue);
}

TEST(MyUniquePtrTest, FunctionResetNullEqualsNull)
{
  MyUniquePtr<TestObject> myUniquePtr;
  myUniquePtr.reset();
  auto nullValue = myUniquePtr.get();
  auto expected = nullptr;

  EXPECT_EQ(expected, nullValue);
}

TEST(MyUniquePtrTest, MoveConstructorOriginalEqualsNullTest) 
{
  MyUniquePtr<TestObject> originalPtr(new TestObject(20));
  MyUniquePtr<TestObject> movedPtr(std::move(originalPtr));
  auto nullValue = originalPtr.get();
  auto expected = nullptr;

  EXPECT_EQ(expected, nullValue);
}

TEST(MyUniquePtrTest, MoveConstructorMovedNotEqualsNullTest) 
{
  MyUniquePtr<TestObject> originalPtr(new TestObject(20));
  MyUniquePtr<TestObject> movedPtr(std::move(originalPtr));
  auto nullValue = movedPtr.get();
  auto notExpected = nullptr;

  EXPECT_NE(notExpected, nullValue);
}

TEST(MyUniquePtrTest, MoveOperatorMoveOriginalPtrEqualsNullTest) 
{
  MyUniquePtr<TestObject> originalPtr(new TestObject(20));
  auto newPtr = std::move(originalPtr);
  auto nullValue = originalPtr.get();
  auto expected = nullptr;

  EXPECT_EQ(expected, nullValue);
}

TEST(MyUniquePtrTest, MoveOperatorMoveNewPtrNotEqualsNullTest) 
{
  MyUniquePtr<TestObject> originalPtr(new TestObject(20));
  auto newPtr = std::move(originalPtr);
  auto notNullValue = newPtr.get();
  auto notExpected = nullptr;

  EXPECT_NE(notExpected, notNullValue);
}

TEST(MyUniquePtrTest, FunctionReleaseOriginalPtrEqualsNullTest) 
{
  MyUniquePtr<TestObject> originalPtr(new TestObject(20));
  originalPtr.release();
  auto expected = nullptr;
  auto nullValue = originalPtr.get();

  EXPECT_EQ(expected, nullValue);
}

TEST(MyUniquePtrTest, FunctionReleaseNewPtrNotEqualsNullTest) 
{
  MyUniquePtr<TestObject> originalPtr(new TestObject(20));
  auto newPtr = originalPtr.release();
  auto notExpected = nullptr;

  EXPECT_NE(notExpected, newPtr);
  delete newPtr; //has to be deleted
}
