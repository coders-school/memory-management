#include "InvalidDereference.hpp"
#include "gtest/gtest.h"
#include "uniquePtr.hpp"

constexpr double testingValue = 10.0;
constexpr double testingOtherValue = 20.0;

class UniquePtrTest : public testing::Test {
public:
    UniquePtrTest()
        : testUniquePtr_(new double{testingValue}) {}

protected:
    coders_school::unique_ptr<double> testUniquePtr_;
};

class UniquePtrArrowOperatorTest {
public:
    double returningTestingValue() { return testingValue; }
};

TEST(UniquePtrTestArrowOperator, ArrowOperatorShouldGuaranteeAcessToStructuresAndUnions) {
    coders_school::unique_ptr<UniquePtrArrowOperatorTest> testUniquePtr_(new UniquePtrArrowOperatorTest{});
    EXPECT_EQ(testUniquePtr_->returningTestingValue(), testingValue);
}

TEST_F(UniquePtrTest, OperatorDereferenceOfUniquePtrShouldDereference) {
    EXPECT_EQ(*testUniquePtr_, testingValue);
}

TEST_F(UniquePtrTest, OperatorDereferenceOfUniquePtrShouldNotDereferenceNullptr) {
    coders_school::unique_ptr<double> testUniquePtr_;
    EXPECT_THROW(*testUniquePtr_, InvalidDereference);
}

TEST_F(UniquePtrTest, UniquePtrShouldMovingOwnershipToAnotherUnqiuePtr) {
    coders_school::unique_ptr<double> testNewPtr = std::move(testUniquePtr_);
    EXPECT_EQ(*testNewPtr, testingValue);
    EXPECT_EQ(testUniquePtr_.get(), nullptr);
}

TEST_F(UniquePtrTest, UniquePtrShouldMovingOwnershipToAnotherUnqiuePtrThroughConctructor) {
    coders_school::unique_ptr<double> testNewPtr{std::move(testUniquePtr_)};
    EXPECT_EQ(*testNewPtr, testingValue);
    EXPECT_EQ(testUniquePtr_.get(), nullptr);
}

TEST_F(UniquePtrTest, MethodGetShouldReturnPtrAdress) {
    auto testPtr = testUniquePtr_.get();
    EXPECT_EQ(*testPtr, *testUniquePtr_);
}

TEST_F(UniquePtrTest, MethodReleaseShouldReleaseOwnership) {
    auto testPtr = testUniquePtr_.release();
    EXPECT_EQ(*testPtr, testingValue);
    EXPECT_EQ(testUniquePtr_.get(), nullptr);
    delete testPtr;
}

TEST_F(UniquePtrTest, MethodResetShouldDeleteOldPtrAndSetPtrWithProvidedValue) {
    testUniquePtr_.reset(new double{testingValue});
    EXPECT_EQ(*testUniquePtr_, testingValue);
}

TEST_F(UniquePtrTest, MethodResetShouldDeleteOldPtrAndSetItToNullptrByDeafult) {
    testUniquePtr_.reset();
    EXPECT_EQ(testUniquePtr_.get(), nullptr);
}

TEST_F(UniquePtrTest, UniquePointerShouldChangeValue) {
    *testUniquePtr_ = testingOtherValue;
    EXPECT_EQ(*testUniquePtr_, testingOtherValue);
}