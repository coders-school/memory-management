#include <gtest/gtest.h>

#include "SharedPtr.hpp"

namespace TestConst {
constexpr int intValue = 5;
constexpr double dobuleValue = 4.2;
constexpr double point_x = 2.2;
constexpr double point_y = 4.2;
constexpr double pointsMultiplication = point_x * point_y;
}  // namespace TestConst

struct SharedPtrTest : ::testing::Test {
    SharedPtrTest()
        : intValuePtr(new int{TestConst::intValue}),
          doubleValuePtr(new double{TestConst::dobuleValue}) {}

    cs::SharedPtr<int> intValuePtr;
    cs::SharedPtr<double> doubleValuePtr;
};

struct Point2D {
    double x = TestConst::point_x;
    double y = TestConst::point_y;
    double ComputeMultiplication() { return x * y; }
};

TEST_F(SharedPtrTest, shouldDereferencePointer) {
    ASSERT_EQ(*intValuePtr, TestConst::intValue);
    ASSERT_EQ(*doubleValuePtr, TestConst::dobuleValue);
}

TEST_F(SharedPtrTest, shouldCopySharedPtr) {
    auto intPtrCopy(intValuePtr);
    auto doublePtrCopy = doubleValuePtr;

    ASSERT_EQ(*intValuePtr, *intPtrCopy);
    ASSERT_EQ(*doubleValuePtr, *doublePtrCopy);
}

TEST_F(SharedPtrTest, operationCopySharedPtrShouldStorePointerToTheSameAddress) {
    auto intPtrCopy(intValuePtr);
    auto doublePtrCopy = doubleValuePtr;

    ASSERT_EQ(intValuePtr.get(), intPtrCopy.get());
    ASSERT_EQ(doubleValuePtr.get(), doublePtrCopy.get());
}

TEST_F(SharedPtrTest, shouldMoveSharedPtr) {
    auto anotherIntPtr(std::move(intValuePtr));
    ASSERT_EQ(*anotherIntPtr, TestConst::intValue);

    auto nextPtr = std::move(anotherIntPtr);
    ASSERT_EQ(*nextPtr, TestConst::intValue);

    ASSERT_EQ(intValuePtr.get(), nullptr);
    ASSERT_EQ(anotherIntPtr.get(), nullptr);
}

TEST_F(SharedPtrTest, shouldReturnUseCountAndIncrementCounterAndDecrementCounter) {
    ASSERT_EQ(intValuePtr.useCount(), 1);
    auto ptr2 = intValuePtr;
    ASSERT_EQ(intValuePtr.useCount(), 2);
    ASSERT_EQ(ptr2.useCount(), 2);
    {
        auto ptr3 = intValuePtr;
        ASSERT_EQ(intValuePtr.useCount(), 3);
        ASSERT_EQ(ptr2.useCount(), 3);
        ASSERT_EQ(ptr3.useCount(), 3);
    }

    ASSERT_EQ(intValuePtr.useCount(), 2);
    ASSERT_EQ(ptr2.useCount(), 2);
}

TEST_F(SharedPtrTest, shouldCastSharedPtrToBool) {
    cs::SharedPtr<int> emptyPtr;

    ASSERT_TRUE(intValuePtr);
    ASSERT_TRUE(doubleValuePtr);
    ASSERT_FALSE(emptyPtr);
}

TEST_F(SharedPtrTest, shouldResetSharedPtr) {
    intValuePtr.reset();

    ASSERT_EQ(intValuePtr.get(), nullptr);

    constexpr int newValue = 42;
    int* newPtr = new int{newValue};

    intValuePtr.reset(newPtr);

    ASSERT_EQ(*intValuePtr, newValue);
    ASSERT_EQ(*newPtr, newValue);
}

TEST_F(SharedPtrTest, shouldDecrementCounterAfterReset) {
    auto newPtr = intValuePtr;
    ASSERT_EQ(intValuePtr.useCount(), 2);
    intValuePtr.reset(nullptr);
    ASSERT_EQ(intValuePtr.useCount(), 1);
}

TEST_F(SharedPtrTest, decrementCounterShouldntDestroyObject) {
    {
        auto newPtr = intValuePtr;
    }
    ASSERT_EQ(*intValuePtr, TestConst::intValue);
}

TEST(Point2D, shouldUseArrowOperator) {
    cs::SharedPtr<Point2D> ptr(new Point2D{});

    ASSERT_EQ(ptr->ComputeMultiplication(), TestConst::pointsMultiplication);
}

TEST(Point2D, shouldCreateSharedPtrWithMakeShared) {
    auto point = new Point2D{};
    cs::SharedPtr<Point2D> sharedPtr = cs::make_shared<Point2D>(point);

    ASSERT_EQ(sharedPtr->ComputeMultiplication(), TestConst::pointsMultiplication);
}
/*
TEST_F(SharedPtrTest, shouldCreateSharedPtrFromWeakPtr) {
    cs::weak_ptr<int> wptr{ptr};

    cs::shared_ptr<int> sptr{wptr};

    ASSERT_EQ(sptr.get(), ptr.get());
}
*/