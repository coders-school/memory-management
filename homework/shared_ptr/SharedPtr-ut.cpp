#include <gtest/gtest.h>

#include "SharedPtr.hpp"

namespace SharedPtrTestConst {
constexpr int intValue = 5;
constexpr double dobuleValue = 4.2;
constexpr double point_x = 2.2;
constexpr double point_y = 4.2;
constexpr double pointsMultiplication = point_x * point_y;
constexpr size_t zeroUseCount = 0;
constexpr size_t oneUseCount = 1;
constexpr size_t twoUseCount = 2;
constexpr size_t threeUseCount = 3;
}  // namespace SharedPtrTestConst

struct SharedPtrTest : ::testing::Test {
    SharedPtrTest()
        : intValuePtr(new int{SharedPtrTestConst::intValue}),
          doubleValuePtr(new double{SharedPtrTestConst::dobuleValue}) {}

    cs::SharedPtr<int> intValuePtr;
    cs::SharedPtr<double> doubleValuePtr;
};

struct Point2D {
    Point2D(double xx, double yy) : x(xx), y(yy) {}
    double x = SharedPtrTestConst::point_x;
    double y = SharedPtrTestConst::point_y;
    double ComputeMultiplication() { return x * y; }
};

TEST_F(SharedPtrTest, shouldDereferencePointer) {
    ASSERT_EQ(*intValuePtr, SharedPtrTestConst::intValue);
    ASSERT_EQ(*doubleValuePtr, SharedPtrTestConst::dobuleValue);
}

TEST_F(SharedPtrTest, shouldCopySharedPtrAndIncrementCounterAndCopiedSharedPtrShouldStoreTheSameAddress) {
    ASSERT_EQ(intValuePtr.use_count(), SharedPtrTestConst::oneUseCount);
    ASSERT_EQ(doubleValuePtr.use_count(), SharedPtrTestConst::oneUseCount);

    auto intPtrCopy(intValuePtr);
    auto doublePtrCopy = doubleValuePtr;

    ASSERT_EQ(intValuePtr.use_count(), SharedPtrTestConst::twoUseCount);
    ASSERT_EQ(doubleValuePtr.use_count(), SharedPtrTestConst::twoUseCount);

    ASSERT_EQ(*intValuePtr, *intPtrCopy);
    ASSERT_EQ(*doubleValuePtr, *doublePtrCopy);

    ASSERT_EQ(intValuePtr.get(), intPtrCopy.get());
    ASSERT_EQ(doubleValuePtr.get(), doublePtrCopy.get());
}

TEST_F(SharedPtrTest, operationCopySharedPtrShouldStorePointerToTheSameAddress) {
    auto intPtrCopy(intValuePtr);
    auto doublePtrCopy = doubleValuePtr;
}

TEST_F(SharedPtrTest, shouldMoveSharedPtr) {
    ASSERT_EQ(intValuePtr.use_count(), SharedPtrTestConst::oneUseCount);

    auto anotherIntPtr(std::move(intValuePtr));

    ASSERT_EQ(intValuePtr.use_count(), SharedPtrTestConst::zeroUseCount);
    ASSERT_EQ(anotherIntPtr.use_count(), SharedPtrTestConst::oneUseCount);
    ASSERT_EQ(*anotherIntPtr, SharedPtrTestConst::intValue);

    auto nextPtr = std::move(anotherIntPtr);
    ASSERT_EQ(*nextPtr, SharedPtrTestConst::intValue);

    ASSERT_EQ(anotherIntPtr.use_count(), SharedPtrTestConst::zeroUseCount);
    ASSERT_EQ(intValuePtr.get(), nullptr);
    ASSERT_EQ(anotherIntPtr.get(), nullptr);
}

TEST_F(SharedPtrTest, shouldReturnUseCountAndIncrementCounterAndDecrementCounter) {
    ASSERT_EQ(intValuePtr.use_count(), SharedPtrTestConst::oneUseCount);
    auto ptr2 = intValuePtr;
    ASSERT_EQ(intValuePtr.use_count(), SharedPtrTestConst::twoUseCount);
    ASSERT_EQ(ptr2.use_count(), SharedPtrTestConst::twoUseCount);
    {
        auto ptr3 = intValuePtr;
        ASSERT_EQ(intValuePtr.use_count(), SharedPtrTestConst::threeUseCount);
        ASSERT_EQ(ptr2.use_count(), SharedPtrTestConst::threeUseCount);
        ASSERT_EQ(ptr3.use_count(), SharedPtrTestConst::threeUseCount);
    }

    ASSERT_EQ(intValuePtr.use_count(), SharedPtrTestConst::twoUseCount);
    ASSERT_EQ(ptr2.use_count(), SharedPtrTestConst::twoUseCount);
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
    ASSERT_FALSE(intValuePtr);

    constexpr int newValue = 42;
    int* newPtr = new int{newValue};

    intValuePtr.reset(newPtr);

    ASSERT_EQ(*intValuePtr, newValue);
    ASSERT_EQ(*newPtr, newValue);
}

TEST_F(SharedPtrTest, shouldDecrementCounterAfterReset) {
    auto newPtr = intValuePtr;
    ASSERT_EQ(intValuePtr.use_count(), SharedPtrTestConst::twoUseCount);
    ASSERT_EQ(newPtr.use_count(), SharedPtrTestConst::twoUseCount);
    intValuePtr.reset(nullptr);
    ASSERT_EQ(newPtr.use_count(), SharedPtrTestConst::oneUseCount);
    ASSERT_EQ(intValuePtr.use_count(), SharedPtrTestConst::zeroUseCount);
    newPtr.reset(nullptr);
    ASSERT_EQ(newPtr.use_count(), SharedPtrTestConst::zeroUseCount);
}

TEST_F(SharedPtrTest, decrementCounterShouldntDestroyObject) {
    {
        auto newPtr = intValuePtr;
    }
    ASSERT_EQ(*intValuePtr, SharedPtrTestConst::intValue);
}

TEST(Point2D, shouldUseArrowOperator) {
    cs::SharedPtr<Point2D> ptr(new Point2D{SharedPtrTestConst::point_x, SharedPtrTestConst::point_y});

    ASSERT_EQ(ptr->ComputeMultiplication(), SharedPtrTestConst::pointsMultiplication);
}

TEST(Point2D, shouldCreateSharedPtrWithMakeShared) {
    cs::SharedPtr<Point2D> sharedPtr = cs::make_shared<Point2D>(SharedPtrTestConst::point_x, SharedPtrTestConst::point_y);

    ASSERT_EQ(sharedPtr->ComputeMultiplication(), SharedPtrTestConst::pointsMultiplication);
}

TEST_F(SharedPtrTest, shouldCreateSharedPtrFromWeakPtr) {
    cs::WeakPtr<int> weakPtr{intValuePtr};

    cs::SharedPtr<int> sharedPtr{weakPtr};

    ASSERT_EQ(sharedPtr.get(), intValuePtr.get());
    ASSERT_EQ(sharedPtr.use_count(), SharedPtrTestConst::twoUseCount);
}
