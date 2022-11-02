#include "unique_ptr.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace my_unique_ptr::test {
using testing::A;
using testing::An;

TEST(getShould, returnPointerOfCorrectType) {
    unique_ptr<int> sutForInt;
    unique_ptr<double> sutForDouble;
    unique_ptr<std::string> sutForString;

    EXPECT_THAT(sutForInt.get(), An<int*>());
    EXPECT_THAT(sutForDouble.get(), A<double*>());
    EXPECT_THAT(sutForString.get(), A<std::string*>());
}

TEST(defaultConstructorShould, InitializeInternalPointerToNullptr) {
    unique_ptr<int> sutForInt;
    unique_ptr<double> sutForDouble;
    unique_ptr<std::string> sutForString;

    EXPECT_EQ(sutForInt.get(), nullptr);
    EXPECT_EQ(sutForDouble.get(), nullptr);
    EXPECT_EQ(sutForString.get(), nullptr);
    EXPECT_EQ(unique_ptr<float>().get(), nullptr);
}

TEST(constructorTakingPointerShould, InitializeInternalPointerToPassedPointer) {
    int* comparisonPTr = new int(42);
    double* comparisonPTr2 = new double(100.0);

    unique_ptr<int> sutForInt(comparisonPTr);
    unique_ptr<double> sutForDouble(comparisonPTr2);

    int* internalPtr = sutForInt.get();
    double* internalPtr2 = sutForDouble.get();

    EXPECT_EQ(internalPtr, comparisonPTr);
    EXPECT_EQ(*internalPtr, 42);
    EXPECT_EQ(internalPtr2, comparisonPTr2);
    EXPECT_EQ(*internalPtr2, 100.0);
}

TEST(constructorTakingRvalueRefferenceShould, initilizeInternalPtrFromPassedArgumentAndSetSourceInternalPtrToNullptr) {
    unique_ptr<int> ptrToBeMoved = new int(42);

    unique_ptr<int> sut(std::move(ptrToBeMoved));
    int* internalPtr = sut.get();

    EXPECT_EQ(ptrToBeMoved.get(), nullptr);
    EXPECT_EQ(*internalPtr, 42);
}

TEST(movingAssignementShould, initilizeInternalPtrFromPassedArgumentAndSetSourceInternalPtrToNullptr) {
    unique_ptr<int> ptrToBeMoved = new int(42);
    unique_ptr<int> sut;
    ASSERT_EQ(sut.get(), nullptr);

    sut = std::move(ptrToBeMoved);
    int* internalPtr = sut.get();

    EXPECT_EQ(ptrToBeMoved.get(), nullptr);
    EXPECT_EQ(*internalPtr, 42);
}

class DestroyingTesterMock {
public:
    ~DestroyingTesterMock() {
        destroyObject();
    }
    MOCK_METHOD(bool, destroyObject, ());
};

TEST(destructorShould, DestroyTheManagedObject) {
    DestroyingTesterMock* mock = new DestroyingTesterMock;
    EXPECT_CALL(*mock, destroyObject);

    {
        unique_ptr<DestroyingTesterMock>{mock};
    }
}

TEST(releaseShould, returnManagedPointeraAndSetInternalPointerToNullptr) {
    int* ptrToBeFilled{nullptr};
    unique_ptr<int> sut{new int(200)};
    ASSERT_NE(sut.get(), nullptr);
    int* expectedValueOfPtrToBeReleased = sut.get();

    ptrToBeFilled = sut.release();

    EXPECT_EQ(expectedValueOfPtrToBeReleased, ptrToBeFilled);
    EXPECT_EQ(sut.get(), nullptr);
}

TEST(resetShould, copyThePassedPtrIntoInternalPtr) {
    int* ptrToBeSetOnSut = new int{20};
    unique_ptr<int> sut;
    ASSERT_EQ(sut.get(), nullptr);

    sut.reset(ptrToBeSetOnSut);

    EXPECT_EQ(sut.get(), ptrToBeSetOnSut);
}

TEST(resetShould, destroyPreviouslyManagedPtr) {
    DestroyingTesterMock* mock = new DestroyingTesterMock;
    unique_ptr<DestroyingTesterMock> sut{mock};

    EXPECT_CALL(*mock, destroyObject);
    sut.reset(new DestroyingTesterMock);
}

TEST(resetShould, setInternalPtrToNullptrIfArgumentListIsEmpty) {
    unique_ptr<int> sut{new int(42)};
    ASSERT_NE(sut.get(), nullptr);

    sut.reset();

    EXPECT_EQ(sut.get(), nullptr);
}

TEST(operatorStarShould, returnReferenceToPointedType) {
    unique_ptr<double> sut(new double{30.0});

    double& expectedReturn = *sut;

    EXPECT_THAT(*sut, A<const double&>());
    EXPECT_EQ(expectedReturn, 30.0);
    // additional check: if the reference allows changes of referenced object
    expectedReturn = 10.0;

    EXPECT_EQ(*sut, 10.0);
}

TEST(arrowOperatorShould, returnPointerToManagedObjectOfCorrectType) {
    unique_ptr<double> sut(new double{30.0});

    EXPECT_THAT(sut.operator->(), A<double*>());
}

struct simpleStructForTesting {
    double someField = 0.0;
};

TEST(arrowOperatorShould, allowAccessToFieldsAndFunctionsOfManagedObject) {
    unique_ptr<std::string> sut(new std::string{"TESTING"});
    unique_ptr<simpleStructForTesting> sut2(new simpleStructForTesting);

    EXPECT_EQ(sut->length(), 7);
    EXPECT_EQ(sut2->someField, 0.0);

    // additional checks: if the pointer retrieved allows changes of managed object
    sut->append("-CHANGED");
    sut2->someField = 200.0;

    EXPECT_EQ(sut->length(), 15);
    EXPECT_EQ(sut2->someField, 200.0);
}

TEST(operatorBoolShould, indicateIfThePointerToManagedObjectIsSet) {
    unique_ptr<float> sut;
    unique_ptr<std::string> sut2 = new std::string{"TESTING"};

    EXPECT_FALSE(sut);
    EXPECT_TRUE(sut2);
}

}  // namespace my_unique_ptr::test
