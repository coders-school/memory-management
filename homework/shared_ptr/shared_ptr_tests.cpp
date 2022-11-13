#include "shared_ptr.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace tests {
using testing::A;
using testing::An;
using testing::NiceMock;

class CustomDeletionDetectorMock {
public:
    MOCK_METHOD(void, detectCustomDeletion, ());
};

template <typename ElementType>
void customDeleter(ElementType* managedObj) {
    delete managedObj;
}

template <>
void customDeleter(CustomDeletionDetectorMock* managedObject) {
    managedObject->detectCustomDeletion();
    delete managedObject;
}

class DeleteCallDetectorMock {
public:
    MOCK_METHOD(void, detectDeleteCall, ());
    ~DeleteCallDetectorMock() {
        detectDeleteCall();
    }
};

class DummyBase {
public:
    virtual ~DummyBase() = default;
};

class DummyDerived : public DummyBase {};

TEST(SharedPtrShould, bePossibleToBeCratedUsingDefaultConstructor) {
    [[maybe_unused]] my::shared_ptr<int> sut{};
    [[maybe_unused]] my::shared_ptr<double> sut2{};
    [[maybe_unused]] my::shared_ptr<std::string> sut3;
}

TEST(SharedPtrShould, storeNullPtrAfterCreationWithDefaultConstructor) {
    my::shared_ptr<int> sut{};
    my::shared_ptr<double> sut2{};
    my::shared_ptr<std::string> sut3;

    EXPECT_EQ(sut.get(), nullptr);
    EXPECT_EQ(sut2.get(), nullptr);
    EXPECT_EQ(sut3.get(), nullptr);
}

TEST(SharedPtrShould, returnUseCountEqualZeroAfterCreationWithDefaultConstructor) {
    my::shared_ptr<int> sut{};
    my::shared_ptr<double> sut2{};
    my::shared_ptr<std::string> sut3;

    EXPECT_EQ(sut.use_count(), 0);
    EXPECT_EQ(sut2.use_count(), 0);
    EXPECT_EQ(sut3.use_count(), 0);
}

TEST(SharedPtrShould, bePossibleToBeCreatedWhenPassedNullptr) {
    [[maybe_unused]] my::shared_ptr<int> sut{nullptr};
    [[maybe_unused]] my::shared_ptr<double> sut2{nullptr};
    [[maybe_unused]] my::shared_ptr<std::string> sut3{nullptr};
}

TEST(SharedPtrShould, storeNullPtrAfterCreationWithNullPtrPassed) {
    my::shared_ptr<int> sut{nullptr};
    my::shared_ptr<double> sut2{nullptr};
    my::shared_ptr<std::string> sut3{nullptr};

    EXPECT_EQ(sut.get(), nullptr);
    EXPECT_EQ(sut2.get(), nullptr);
    EXPECT_EQ(sut3.get(), nullptr);
}

TEST(SharedPtrShould, returnUseCountEqualZeroAfterCreationWithNullPtrPassed) {
    my::shared_ptr<int> sut{nullptr};
    my::shared_ptr<double> sut2{nullptr};
    my::shared_ptr<std::string> sut3{nullptr};

    EXPECT_EQ(sut.use_count(), 0);
    EXPECT_EQ(sut2.use_count(), 0);
    EXPECT_EQ(sut3.use_count(), 0);
}

TEST(SharedPtrShould, storeNullPtrAfterCreationWithNullPtrAndDeleterPassed) {
    my::shared_ptr<int> sut{nullptr, customDeleter<int>};
    my::shared_ptr<double> sut2{nullptr, customDeleter<double>};
    my::shared_ptr<std::string> sut3{nullptr, customDeleter<std::string>};

    EXPECT_EQ(sut.get(), nullptr);
    EXPECT_EQ(sut2.get(), nullptr);
    EXPECT_EQ(sut3.get(), nullptr);
}

TEST(SharedPtrShould, returnUseCountEqualZeroAfterCreationWithNullPtrAndDeleterPassed) {
    my::shared_ptr<int> sut{nullptr, customDeleter<int>};
    my::shared_ptr<double> sut2{nullptr, customDeleter<double>};
    my::shared_ptr<std::string> sut3{nullptr, customDeleter<std::string>};

    EXPECT_EQ(sut.use_count(), 0);
    EXPECT_EQ(sut2.use_count(), 0);
    EXPECT_EQ(sut3.use_count(), 0);
}

TEST(SharedPtrShould, bePossibleToBeCreatedWhenPassedPtrToSameTypeDeclared) {
    [[maybe_unused]] my::shared_ptr<int> sut{new int{}};
    [[maybe_unused]] my::shared_ptr<double> sut2{new double{}};
    [[maybe_unused]] my::shared_ptr<std::string> sut3{new std::string};
}

TEST(SharedPtrShould, storePtrPassedDuringConstructionWithPointerToDeclaredType) {
    int* ptr = new int(10);
    std::string* ptr2 = new std::string{"TEST"};

    my::shared_ptr<int> sut{ptr};
    my::shared_ptr<std::string> sut2{ptr2};

    EXPECT_EQ(sut.get(), ptr);
    EXPECT_EQ(sut2.get(), ptr2);
    EXPECT_EQ(*sut.get(), 10);
    EXPECT_EQ(*sut2.get(), "TEST");
}

TEST(SharedPtrShould, haveUseCountEqualToOneAfterConstructionWithPointerToDeclaredType) {
    my::shared_ptr<int> sut{new int};
    my::shared_ptr<std::string> sut2{new std::string};

    EXPECT_EQ(sut.use_count(), 1);
    EXPECT_EQ(sut2.use_count(), 1);
}

TEST(SharedPtrShould, bePossibleToBeCreatedWhenPassedConvertiblePointer) {
    [[maybe_unused]] my::shared_ptr<DummyBase> sut3{new DummyDerived};
}

TEST(SharedPtrShould, storePtrPassedDuringConstructionWithConvertiblePointer) {
    DummyDerived* ptr = new DummyDerived;
    my::shared_ptr<DummyBase> sut{ptr};

    EXPECT_EQ(sut.get(), ptr);
    EXPECT_THAT(sut.get(), A<DummyBase*>());
}

TEST(SharedPtrShould, haveUseCountEqualToOneAfterConstructionWithConvertiblePointer) {
    my::shared_ptr<DummyBase> sut{new DummyDerived};
    EXPECT_EQ(sut.use_count(), 1);
}

TEST(SharedPtrsCopyConstructorShould, copyTheValueOfPtrOfSource) {
    my::shared_ptr<double> null_sut{nullptr};
    my::shared_ptr<double> sut{new double{10.0}};

    ASSERT_EQ(null_sut.get(), nullptr);
    ASSERT_NE(sut.get(), nullptr);

    my::shared_ptr<double> null_sut_copy{null_sut};
    my::shared_ptr<double> sut_copy{sut};

    EXPECT_EQ(null_sut.get(), null_sut_copy.get());
    EXPECT_EQ(sut.get(), sut_copy.get());
    EXPECT_EQ(*sut_copy.get(), 10.0);
}

TEST(SharedPtrsCopyConstructorShould, increaseSharedCounterIfSourceHadManagedObject) {
    my::shared_ptr<double> sut{new double{10.0}};
    ASSERT_NE(sut.get(), nullptr);
    ASSERT_EQ(sut.use_count(), 1);

    my::shared_ptr<double> sut_copy{sut};
    EXPECT_EQ(sut_copy.use_count(), 2);
    EXPECT_EQ(sut.use_count(), 2);

    my::shared_ptr<double> sut_copy2{sut};
    EXPECT_EQ(sut_copy2.use_count(), 3);
    EXPECT_EQ(sut_copy.use_count(), 3);
    EXPECT_EQ(sut.use_count(), 3);
}

TEST(SharedPtrsCopyConstructorShould, notIncreaseSharedCounterIfSourceDidNotManageAnyObject) {
    my::shared_ptr<double> sut{};
    ASSERT_EQ(sut.get(), nullptr);
    ASSERT_EQ(sut.use_count(), 0);

    my::shared_ptr<double> sut_copy{sut};
    EXPECT_EQ(sut_copy.use_count(), 0);
    EXPECT_EQ(sut.use_count(), 0);
}

TEST(SharedPtrsCopyConstructorShould,
     copyTheValueOfPtrOfSourceIfSourcePointerIsConvertibleToDestinationPtr) {
    my::shared_ptr<DummyDerived> sut{new DummyDerived};
    ASSERT_NE(sut.get(), nullptr);

    my::shared_ptr<DummyBase> sut_copy{sut};

    EXPECT_EQ(sut.get(), sut_copy.get());
}

TEST(SharedPtrsCopyConstructorShould,
     increaseSharedCounterIfSourceHadManagedObjectAndConvertiblePtrToDestinationPtr) {
    my::shared_ptr<DummyDerived> sut{new DummyDerived};
    ASSERT_NE(sut.get(), nullptr);
    ASSERT_EQ(sut.use_count(), 1);

    my::shared_ptr<DummyBase> sut_copy{sut};
    EXPECT_EQ(sut_copy.use_count(), 2);
    EXPECT_EQ(sut.use_count(), 2);

    my::shared_ptr<DummyBase> sut_copy2{sut};
    EXPECT_EQ(sut_copy2.use_count(), 3);
    EXPECT_EQ(sut_copy.use_count(), 3);
    EXPECT_EQ(sut.use_count(), 3);
}

TEST(SharedPtrShould, bePossibleToBeCreatedWhenPassedConvertiblePointerForCustomDeleterUsed) {
    [[maybe_unused]] my::shared_ptr<DummyBase> sut{new DummyDerived, customDeleter<DummyBase>};
}

TEST(SharedPtrShould, storePtrPassedDuringConstructionWithConvertiblePointerAndCustomdeleter) {
    DummyDerived* ptr = new DummyDerived;
    my::shared_ptr<DummyBase> sut{ptr, customDeleter<DummyBase>};

    EXPECT_EQ(sut.get(), ptr);
    EXPECT_THAT(sut.get(), A<DummyBase*>());
}

TEST(SharedPtrShould, haveUseCountEqualToOneAfterConstructionWithConvertiblePointerAndDeleterPassed) {
    my::shared_ptr<DummyBase> sut{new DummyDerived, customDeleter<DummyBase>};
    EXPECT_EQ(sut.use_count(), 1);
}

TEST(SharedPtrGetShould, returnValueOfStoredPtr) {
    int* ptr = new int(30);
    my::shared_ptr<int> sut(ptr);

    EXPECT_THAT(sut.get(), An<int*>());
    EXPECT_EQ(sut.get(), ptr);
    EXPECT_EQ(*sut.get(), 30);
}

TEST(SharedPtrUseCountShould, returnNumberOfSharedPointersSharingResource) {
    my::shared_ptr<int> sut(new int);
    my::shared_ptr<int> null_sut;

    EXPECT_EQ(sut.use_count(), 1);
    EXPECT_EQ(null_sut.use_count(), 0);
}

TEST(SharedPtrDestructorShould, destroyManagedObjecIfNoDeleterSpecifiedAndLastInstanceDestroyed) {
    my::shared_ptr<DeleteCallDetectorMock> sut(new DeleteCallDetectorMock);
    DeleteCallDetectorMock* testMock = sut.get();

    EXPECT_CALL(*testMock, detectDeleteCall);
}

TEST(SharedPtrDestructorShould, callCustomDeleterOnDestructionIfLastInstanceDestroyed) {
    auto deleter = customDeleter<CustomDeletionDetectorMock>;
    my::shared_ptr<CustomDeletionDetectorMock> sut{new CustomDeletionDetectorMock, deleter};
    CustomDeletionDetectorMock* testMock = sut.get();

    EXPECT_CALL(*testMock, detectCustomDeletion);
}
// TODO:
// TEST(SharedPtrDestructorShould, decreaseSharedCounterOnlyIfMoreThanOneInstanceExist){

// }

// TODO: add test for deletion of control block if weak count ==

}  // namespace tests