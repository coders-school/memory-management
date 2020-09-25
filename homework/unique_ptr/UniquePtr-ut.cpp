#include <gtest/gtest.h>

#include "NullptrException.hpp"
#include "UniquePtr.hpp"

namespace ConstValues {
constexpr double doubleVal = 42.0;
constexpr double newdoubleVal = 2.2;
}  // namespace ConstValues

struct Square {
    Square(double a, double b)
        : a_(a), b_(b) {}

    double a_;
    double b_;

    double ComputeArea() { return a_ * b_; }
};

struct UniquePtrTest : ::testing::Test {
    UniquePtrTest()
        : doublePtr(new double{ConstValues::doubleVal}) {}

    UniquePtr<double> doublePtr;
};

TEST_F(UniquePtrTest, ShouldDereferencePointer) {
    ASSERT_EQ(*doublePtr, ConstValues::doubleVal);
}

TEST_F(UniquePtrTest, ShouldDereferenceAndChangeValue) {
    *doublePtr = ConstValues::newdoubleVal;
    ASSERT_EQ(*doublePtr, ConstValues::newdoubleVal);
}

TEST_F(UniquePtrTest, ShouldUseMoveAndGet) {
    auto rawPtr = doublePtr.get();
    UniquePtr<double> newDoublePtr = std::move(doublePtr);
    ASSERT_EQ(*newDoublePtr, ConstValues::doubleVal);
    ASSERT_EQ(doublePtr.get(), nullptr);
    ASSERT_EQ(rawPtr, newDoublePtr.get());
}

TEST_F(UniquePtrTest, ShouldUseReset) {
    doublePtr.reset(new double{ConstValues::newdoubleVal});
    ASSERT_EQ(*doublePtr, ConstValues::newdoubleVal);
    doublePtr.reset();
    ASSERT_THROW(*doublePtr, NullptrException);
}

TEST_F(UniquePtrTest, ShouldUseReleaseAndThrowExceptionIfDerefenceNull) {
    auto releasedPtr = doublePtr.release();
    ASSERT_EQ(*releasedPtr, ConstValues::doubleVal);
    ASSERT_EQ(doublePtr.get(), nullptr);
    ASSERT_THROW(*doublePtr, NullptrException);
    delete releasedPtr;
}

TEST_F(UniquePtrTest, ShouldCallMethodByArrowOperator) {
    double a = 3.5;
    double b = 2.0;
    UniquePtr<Square> squarePtr = new Square(a, b);
    ASSERT_EQ(squarePtr->ComputeArea(), a * b);

    squarePtr = new Square (2*a, 2*b);
    ASSERT_EQ(squarePtr->ComputeArea(), 2*a * 2*b);
}
