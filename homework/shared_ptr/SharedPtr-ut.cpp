#include "SharedPtr.hpp"
#include "gtest/gtest.h"

constexpr int testingValue = 10;
constexpr int testingOtherValue = 20;

class SharedPtrTest : public testing::Test {
public:
    SharedPtrTest()
        : testSharedPtr_(new int{testingValue}) {}

protected:
    coders_school::shared_ptr<int> testSharedPtr_;
};

struct arrrowOperatorTest {
    int getTestingValue() const { return testingValue; }
};

TEST_F(SharedPtrTest, OperatorDereferenceOfUniquePtrShouldDereference) {
    EXPECT_EQ(*testSharedPtr_, testingValue);
}

TEST_F(SharedPtrTest, MethodGetShouldReturnPtrAdress) {
    auto testPtr = testSharedPtr_.get();
    EXPECT_EQ(*testSharedPtr_, *testPtr);
}

TEST_F(SharedPtrTest, OperatorDereferenceOfSharedPtrShouldNotDereferenceNullptr) {
    coders_school::shared_ptr<double> shouldThrowAnExcpetionPtr;
    EXPECT_THROW(*shouldThrowAnExcpetionPtr, InvalidDereference);
}

TEST_F(SharedPtrTest, ArrowOperatorShouldGuaranteeAcessToStructuresAndUnions) {
    coders_school::shared_ptr<arrrowOperatorTest> arrowOperatorTest;
    EXPECT_EQ(arrowOperatorTest->getTestingValue(), testingValue);
}

TEST_F(SharedPtrTest, SharedPtrShouldBeCopyable) {
    const int useCountBeforeCopy = 1;
    const int useCountAfterCopy = 2;

    coders_school::shared_ptr<int> copyOfTestPtr(new int{testingValue});
    EXPECT_EQ(copyOfTestPtr.use_count(), useCountBeforeCopy);

    copyOfTestPtr = testSharedPtr_;
    EXPECT_EQ(*copyOfTestPtr, testingValue);
    EXPECT_EQ(copyOfTestPtr.use_count(), useCountAfterCopy);
}

TEST_F(SharedPtrTest, MethodUseCountShouldReturnNumberOfSharedPtrUses) {
    const int useCountTest = 3;

    coders_school::shared_ptr<int> sumOfUses(new int{testingOtherValue});
    coders_school::shared_ptr<int> secondUse = sumOfUses;
    coders_school::shared_ptr<int> thirdUse = sumOfUses;

    EXPECT_EQ(sumOfUses.use_count(), useCountTest);
}

TEST_F(SharedPtrTest, MethodResetShouldDeleteOldPtrAndSetPtrWithProvidedValue) {
    coders_school::shared_ptr<int> testSharedPtr_(new int{testingOtherValue});
    testSharedPtr_.reset(new int{testingValue});
    EXPECT_EQ(*testSharedPtr_, testingValue);
}

TEST_F(SharedPtrTest, SharedPtrShouldMovingOwnershipToAnotherSharedPtrThroughConctructor) {
    const int useCountAfterMove = 1;

    coders_school::shared_ptr<int> moveTestingPtr(std::move(testSharedPtr_));
    EXPECT_EQ(testSharedPtr_.get(), nullptr);
    EXPECT_EQ(*moveTestingPtr, testingValue);
    EXPECT_EQ(moveTestingPtr.use_count(), useCountAfterMove);
}

TEST_F(SharedPtrTest, SharedPtrShouldMovingOwnershipToAnotherSharedPtr) {
    const int moveAssignmentTestValue{4};
    const int useCountBeforeAndAfter{1};

    coders_school::shared_ptr<int> moveTestingPtr(new int{moveAssignmentTestValue});
    EXPECT_EQ(moveTestingPtr.use_count(), useCountBeforeAndAfter);

    moveTestingPtr = std::move(testSharedPtr_);
    EXPECT_EQ(moveTestingPtr.use_count(), useCountBeforeAndAfter);
    EXPECT_EQ(testSharedPtr_.get(), nullptr);
    EXPECT_EQ(*moveTestingPtr, testingValue);
}

TEST_F(SharedPtrTest, SharedPointerShouldChangeValue) {
    *testSharedPtr_ = testingOtherValue;
    EXPECT_EQ(*testSharedPtr_, testingOtherValue);
}
