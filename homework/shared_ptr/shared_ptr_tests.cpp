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
    MOCK_METHOD(void, detectDeleteCallForDerived, ());
    virtual ~DeleteCallDetectorMock() {
        detectDeleteCall();
    }
};

// TODO: VERIFY
class DerivedDeleteCallDetectorMock : public DeleteCallDetectorMock {
public:
    ~DerivedDeleteCallDetectorMock() override {
        detectDeleteCallForDerived();
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

TEST(SharedPtrConstructorTakingConvertiblePointerShould, storePtrPassedDuringConstruction) {
    DummyDerived* ptr = new DummyDerived;
    my::shared_ptr<DummyBase> sut{ptr};

    EXPECT_EQ(sut.get(), ptr);
    EXPECT_THAT(sut.get(), A<DummyBase*>());
}

TEST(SharedPtrConstructorTakingConvertiblePointerShould,
     haveUseCountEqualToOneAfterConstruction) {
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

TEST(SharedPtrsCopyConstructorTakingConvertibleSourceShould,
     copyTheValueOfPtrStoredInSource) {
    my::shared_ptr<DummyDerived> sut{new DummyDerived};
    ASSERT_NE(sut.get(), nullptr);

    my::shared_ptr<DummyBase> sut_copy{sut};

    EXPECT_EQ(sut.get(), sut_copy.get());
}

TEST(SharedPtrsCopyConstructorTakingConvertibleSourceShould,
     increaseSharedCounterIfSourceHadManagedObject) {
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

TEST(SharedPtrsMoveConstructorShould, copyTheValueOfPtrOfSource) {
    my::shared_ptr<double> null_sut{nullptr};
    my::shared_ptr<double> sut{new double{10.0}};
    double* ptr_to_compare = sut.get();

    ASSERT_EQ(null_sut.get(), nullptr);
    ASSERT_NE(sut.get(), nullptr);

    my::shared_ptr<double> null_sut_moved{std::move(null_sut)};
    my::shared_ptr<double> sut_moved{std::move(sut)};

    EXPECT_EQ(nullptr, null_sut_moved.get());
    EXPECT_EQ(ptr_to_compare, sut_moved.get());
    EXPECT_EQ(*sut_moved.get(), 10.0);
}

TEST(SharedPtrsMoveConstructorShould, keepValueOfUseCountFromSource) {
    my::shared_ptr<double> sut{new double{10.0}};
    ASSERT_NE(sut.get(), nullptr);
    ASSERT_EQ(sut.use_count(), 1);

    my::shared_ptr<double> sut_moved{std::move(sut)};
    EXPECT_EQ(sut_moved.use_count(), 1);
}

TEST(SharedPtrsMoveConstructorShould, setManagedPtrOfSourceToNullptr) {
    my::shared_ptr<double> sut{new double{10.0}};
    ASSERT_NE(sut.get(), nullptr);

    my::shared_ptr<double> sut_moved{std::move(sut)};
    EXPECT_EQ(sut.get(), nullptr);
}

TEST(SharedPtrsMoveConstructorTakingConvertibleSourceShould,
     copyTheValueOfPtrOfSource) {
    my::shared_ptr<DummyDerived> sut{new DummyDerived};
    ASSERT_NE(sut.get(), nullptr);
    auto ptr_to_compare = sut.get();

    my::shared_ptr<DummyBase> sut_moved{std::move(sut)};

    EXPECT_EQ(ptr_to_compare, sut_moved.get());
}
TEST(SharedPtrsMoveConstructorTakingConvertibleSourceShould,
     keepValueOfUseCountFromSource) {
    my::shared_ptr<DummyDerived> sut{new DummyDerived};
    ASSERT_NE(sut.get(), nullptr);
    ASSERT_EQ(sut.use_count(), 1);

    my::shared_ptr<DummyBase> sut_moved{std::move(sut)};

    EXPECT_EQ(sut_moved.use_count(), 1);
}

TEST(SharedPtrsMoveConstructorTakingConvertibleSourceShould, setManagedPtrOfSourceToNullptr) {
    my::shared_ptr<DummyDerived> sut{new DummyDerived};
    ASSERT_NE(sut.get(), nullptr);

    my::shared_ptr<DummyBase> sut_moved{std::move(sut)};

    EXPECT_EQ(sut.get(), nullptr);
}

TEST(SharedPtrShould, bePossibleToBeCreatedWhenPassedConvertiblePointerForCustomDeleterUsed) {
    [[maybe_unused]] my::shared_ptr<DummyBase> sut{new DummyDerived, customDeleter<DummyBase>};
}

TEST(SharedPtrConstructorTakingConvertiblePointerAndCustomDeleterShould, storePtrPassedDuringConstruction) {
    DummyDerived* ptr = new DummyDerived;
    my::shared_ptr<DummyBase> sut{ptr, customDeleter<DummyBase>};

    EXPECT_EQ(sut.get(), ptr);
    EXPECT_THAT(sut.get(), A<DummyBase*>());
}

TEST(SharedPtrConstructorTakingConvertiblePointerAndCustomDeleterShould, haveUseCountEqualToOneAfterConstruction) {
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

TEST(SharedPtrOperatorStarShould, returnReferenceToManagedObject) {
    int* ptr = new int(30);
    my::shared_ptr<int> sut(ptr);

    EXPECT_THAT(*sut, An<const int&>());
    EXPECT_EQ(*sut, *ptr);
    EXPECT_EQ(*sut, 30);
}

TEST(SharedPtrArrowOperatorShould, returnPtrToManagedObjectAndAllowMemberAcces) {
    auto managedObj = new std::pair<int, std::string>{5, "five"};

    my::shared_ptr<std::pair<int, std::string>> sut(managedObj);

    EXPECT_THAT(sut.operator->(), (A<std::pair<int, std::string>*>()));
    EXPECT_EQ(sut->first, 5);
    EXPECT_EQ(sut->second, "five");
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

TEST(SharedPtrDestructorShould, decreaseSharedCounterIfMoreThanOneInstanceExist) {
    my::shared_ptr<double> sut1{new double};
    my::shared_ptr<std::string> sut2{new std::string};
    my::shared_ptr<DummyBase> sut3{new DummyDerived};
    {
        auto sut1_copy{sut1};
        auto sut2_copy{sut2};
        auto sut3_copy{sut3};
        {
            auto sut1_copy2{sut1};
            auto sut2_copy2{sut2};
            auto sut3_copy2{sut3};

            EXPECT_EQ(sut1.use_count(), 3);
            EXPECT_EQ(sut1_copy.use_count(), 3);
            EXPECT_EQ(sut2.use_count(), 3);
            EXPECT_EQ(sut2_copy.use_count(), 3);
            EXPECT_EQ(sut3.use_count(), 3);
            EXPECT_EQ(sut3_copy.use_count(), 3);
        }  // first use_count decreased expected
        EXPECT_EQ(sut1.use_count(), 2);
        EXPECT_EQ(sut1_copy.use_count(), 2);
        EXPECT_EQ(sut2.use_count(), 2);
        EXPECT_EQ(sut2_copy.use_count(), 2);
        EXPECT_EQ(sut3.use_count(), 2);
        EXPECT_EQ(sut3_copy.use_count(), 2);
    }  // second use_count decrease expected
    EXPECT_EQ(sut1.use_count(), 1);
    EXPECT_EQ(sut2.use_count(), 1);
    EXPECT_EQ(sut3.use_count(), 1);
}

// TODO: add test for deletion of control block if weak count == 0

TEST(SharedPtrCopyAssignmentShould, decreaseUseCountOfPreviouslyManagedObject) {
    my::shared_ptr<double> sut{new double};
    my::shared_ptr<double> original_sut_copy = sut;
    ASSERT_EQ(sut.use_count(), 2);
    ASSERT_EQ(original_sut_copy.use_count(), 2);

    my::shared_ptr<double> replacing_shared_ptr{new double};
    sut = replacing_shared_ptr;

    EXPECT_EQ(original_sut_copy.use_count(), 1);
}
// TODO: VERIFY potential leak CURRENT NEXT
TEST(SharedPtrCopyAssignmentShould, destroyPreviouslyManagedObjectIfNoMoreCopiesLeft) {
    my::shared_ptr<DeleteCallDetectorMock> sut{new DeleteCallDetectorMock};
    my::shared_ptr<DeleteCallDetectorMock> to_be_copied{new DeleteCallDetectorMock};
    EXPECT_CALL(*sut, detectDeleteCall);

    sut = to_be_copied;

    EXPECT_CALL(*to_be_copied, detectDeleteCall);
}

TEST(SharedPtrCopyAssignmentShould, copyPtrToNewManagedObject) {
    my::shared_ptr<std::string> sut{new std::string("Original")};
    my::shared_ptr<std::string> to_be_copied{new std::string("Replacing")};
    // for empty shared_ptr
    my::shared_ptr<std::string> sut2;
    my::shared_ptr<std::string> to_be_copied2{new std::string("Replacing empty")};

    sut = to_be_copied;
    sut2 = to_be_copied2;

    EXPECT_EQ(to_be_copied.get(), sut.get());
    EXPECT_EQ(*sut.get(), "Replacing");
    EXPECT_EQ(to_be_copied2.get(), sut2.get());
    EXPECT_EQ(*sut2.get(), "Replacing empty");
}

TEST(SharedPtrCopyAssignmentShould, increaseUseCountOfNewManagedObject) {
    my::shared_ptr<int> sut;
    my::shared_ptr<int> to_be_copied{new int};
    ASSERT_EQ(to_be_copied.use_count(), 1);

    sut = to_be_copied;
    EXPECT_EQ(sut.use_count(), 2);
    EXPECT_EQ(to_be_copied.use_count(), 2);
}

// TODO: add test for deletion of control block if weak count == 0 after copy assignment

TEST(SharedPtrCopyAssignmentForConvertibleTypeShould,
     decreaseUseCountOfPreviouslyManagedObject) {
    my::shared_ptr<DummyBase> sut{new DummyBase};
    my::shared_ptr<DummyBase> original_sut_copy = sut;
    ASSERT_EQ(sut.use_count(), 2);
    ASSERT_EQ(original_sut_copy.use_count(), 2);

    my::shared_ptr<DummyDerived> replacing_shared_ptr{new DummyDerived};
    sut = replacing_shared_ptr;

    EXPECT_EQ(original_sut_copy.use_count(), 1);
}

TEST(SharedPtrCopyAssignmentForConvertibleTypeShould,
     destroyPreviouslyManagedObjectIfNoMoreCopiesLeft) {
    my::shared_ptr<DeleteCallDetectorMock> sut{new DerivedDeleteCallDetectorMock};
    my::shared_ptr<DerivedDeleteCallDetectorMock> to_be_copied{new DerivedDeleteCallDetectorMock};

    EXPECT_CALL(*sut, detectDeleteCallForDerived);
    EXPECT_CALL(*sut, detectDeleteCall);

    sut = to_be_copied;

    EXPECT_CALL(*to_be_copied, detectDeleteCallForDerived);
    EXPECT_CALL(*to_be_copied, detectDeleteCall);
}

TEST(SharedPtrCopyAssignmentForConvertibleTypeShould, copyPtrToNewManagedObject) {
    my::shared_ptr<DummyBase> sut{new DummyBase};
    my::shared_ptr<DummyDerived> to_be_copied{new DummyDerived};
    // for empty shared_ptr
    my::shared_ptr<DummyBase> sut2;
    my::shared_ptr<DummyDerived> to_be_copied2{new DummyDerived};

    sut = to_be_copied;
    sut2 = to_be_copied2;

    EXPECT_EQ(to_be_copied.get(), sut.get());
    EXPECT_EQ(to_be_copied2.get(), sut2.get());
}

TEST(SharedPtrCopyAssignmentForConvertibleTypeShould, increaseUseCountOfNewManagedObject) {
    my::shared_ptr<DummyBase> sut;
    my::shared_ptr<DummyDerived> to_be_copied{new DummyDerived};
    ASSERT_EQ(to_be_copied.use_count(), 1);

    sut = to_be_copied;
    EXPECT_EQ(sut.use_count(), 2);
    EXPECT_EQ(to_be_copied.use_count(), 2);
}

// TODO: add test for deletion of control block if weak count == 0 after copy assignment

TEST(SharedPtrMoveAssignmentShould, decreaseUseCountOfPreviouslyManagedObject) {
    my::shared_ptr<double> sut{new double};
    my::shared_ptr<double> original_sut_copy = sut;
    ASSERT_EQ(sut.use_count(), 2);
    ASSERT_EQ(original_sut_copy.use_count(), 2);

    my::shared_ptr<double> moved_shared_ptr{new double};
    sut = std::move(moved_shared_ptr);

    EXPECT_EQ(original_sut_copy.use_count(), 1);
}

TEST(SharedPtrMoveAssignmentShould, destroyPreviouslyManagedObjectIfNoMoreCopiesLeft) {
    my::shared_ptr<DeleteCallDetectorMock> sut{new DeleteCallDetectorMock};
    my::shared_ptr<DeleteCallDetectorMock> sut_to_be_moved{new DeleteCallDetectorMock};
    EXPECT_CALL(*sut, detectDeleteCall);

    sut = std::move(sut_to_be_moved);

    EXPECT_CALL(*sut, detectDeleteCall);
}

TEST(SharedPtrMoveAssignmentShould, copySourceManagedPtr) {
    my::shared_ptr<std::string> sut{new std::string("Original")};
    my::shared_ptr<std::string> to_be_moved{new std::string("Moved")};
    std::string* ptr_to_compare = to_be_moved.get();

    sut = std::move(to_be_moved);

    EXPECT_EQ(ptr_to_compare, sut.get());
    EXPECT_EQ(*sut.get(), "Moved");
}

TEST(SharedPtrMoveAssignmentShould, setManagedPtrOfSourceToNullptr) {
    my::shared_ptr<double> to_be_moved{new double};
    ASSERT_NE(to_be_moved.get(), nullptr);
    my::shared_ptr<double> sut;

    sut = std::move(to_be_moved);

    EXPECT_EQ(to_be_moved.get(), nullptr);
}

TEST(SharedPtrMoveAssignmentShould, keepUseCountOfSourceManagedObject) {
    my::shared_ptr<double> to_be_moved{new double};
    my::shared_ptr<double> sut;
    ASSERT_EQ(to_be_moved.use_count(), 1);
    ASSERT_EQ(sut.use_count(), 0);

    sut = std::move(to_be_moved);

    EXPECT_EQ(sut.use_count(), 1);
}

TEST(SharedPtrMoveAssignmentTakingConvertibleTypeShould, decreaseUseCountOfPreviouslyManagedObject) {
    my::shared_ptr<DummyBase> sut{new DummyBase};
    my::shared_ptr<DummyBase> original_sut_copy = sut;
    ASSERT_EQ(sut.use_count(), 2);
    ASSERT_EQ(original_sut_copy.use_count(), 2);

    my::shared_ptr<DummyDerived> moved_shared_ptr{new DummyDerived};
    sut = std::move(moved_shared_ptr);

    EXPECT_EQ(original_sut_copy.use_count(), 1);
}

TEST(SharedPtrMoveAssignmentTakingConvertibleTypeShould, destroyPreviouslyManagedObjectIfNoMoreCopiesLeft) {
    my::shared_ptr<DeleteCallDetectorMock> sut{new DeleteCallDetectorMock};
    my::shared_ptr<DerivedDeleteCallDetectorMock> sut_to_be_moved{new DerivedDeleteCallDetectorMock};

    EXPECT_CALL(*sut, detectDeleteCall);

    sut = std::move(sut_to_be_moved);

    EXPECT_CALL(*sut, detectDeleteCallForDerived);
    EXPECT_CALL(*sut, detectDeleteCall);
}

TEST(SharedPtrMoveAssignmentTakingConvertibleTypeShould, copySourceManagedPtr) {
    my::shared_ptr<DummyBase> sut{new DummyBase};
    my::shared_ptr<DummyDerived> sut_to_be_moved{new DummyDerived};
    DummyBase* ptr_to_be_compared = sut_to_be_moved.get();

    sut = std::move(sut_to_be_moved);

    EXPECT_EQ(ptr_to_be_compared, sut.get());
}

TEST(SharedPtrMoveAssignmentTakingConvertibleTypeShould, setManagedPtrOfSourceToNullptr) {
    my::shared_ptr<DummyDerived> sut_to_be_moved{new DummyDerived};
    ASSERT_NE(sut_to_be_moved.get(), nullptr);
    my::shared_ptr<DummyBase> sut;

    sut = std::move(sut_to_be_moved);

    EXPECT_EQ(sut_to_be_moved.get(), nullptr);
}

TEST(SharedPtrMoveAssignmentTakingConvertibleTypeShould, keepUseCountOfSourceManagedObject) {
    my::shared_ptr<DummyDerived> sut_to_be_moved{new DummyDerived};
    my::shared_ptr<DummyBase> sut;
    ASSERT_EQ(sut_to_be_moved.use_count(), 1);
    ASSERT_EQ(sut.use_count(), 0);

    sut = std::move(sut_to_be_moved);

    EXPECT_EQ(sut.use_count(), 1);
}

TEST(SharedPtrOperatorBoolShould, returnTrueIfSutManagesAnObjectAndFalseOtherwise) {
    my::shared_ptr<double> sut{};
    my::shared_ptr<int> sut2{new int};

    EXPECT_FALSE(sut);
    EXPECT_TRUE(sut2);
}

TEST(SharedPtrsResetWithoutArgsShould, setManagedPtrToNullPtr) {
    my::shared_ptr<double> sut{new double};
    ASSERT_NE(sut.get(), nullptr);

    sut.reset();

    EXPECT_EQ(sut.get(), nullptr);
}

TEST(SharedPtrsResetWithoutArgsShould, destroyTheManagedObjectAfterResetCalledWhenUseCountIsEqualToOne) {
    my::shared_ptr<DeleteCallDetectorMock> sut{new DeleteCallDetectorMock};
    ASSERT_NE(sut.get(), nullptr);
    ASSERT_EQ(sut.use_count(), 1);
    EXPECT_CALL(*sut, detectDeleteCall);

    sut.reset();
}

TEST(SharedPtrsResetWithoutArgsShould, decreaseUseCountIfOtherSharedPtrsOwnTheResource) {
    my::shared_ptr<double> sut{new double};
    my::shared_ptr<double> sut_copy = sut;
    ASSERT_EQ(sut.use_count(), 2);

    sut_copy.reset();

    EXPECT_EQ(sut.use_count(), 1);
}

TEST(SharedPtrsResetTakingPtrShould, destroyPreviouslyManagedObjectAfterResetCalledWhenUseCountIsEqualToOne) {
    my::shared_ptr<DeleteCallDetectorMock> sut{new DeleteCallDetectorMock};
    ASSERT_NE(sut.get(), nullptr);
    ASSERT_EQ(sut.use_count(), 1);
    EXPECT_CALL(*sut, detectDeleteCall);

    sut.reset(new DerivedDeleteCallDetectorMock);

    EXPECT_CALL(*sut, detectDeleteCallForDerived);
    EXPECT_CALL(*sut, detectDeleteCall);
}

TEST(SharedPtrsResetTakingPtrShould, decreaseUseCountOfPreviouslyManagedPtr) {
    my::shared_ptr<double> sut{new double};
    my::shared_ptr<double> sut_copy = sut;
    my::shared_ptr<DummyBase> sut2{new DummyDerived};
    my::shared_ptr<DummyBase> sut2_copy = sut2;
    ASSERT_EQ(sut.use_count(), 2);
    ASSERT_EQ(sut2.use_count(), 2);

    sut_copy.reset(new double);
    sut2_copy.reset(new DummyDerived);

    EXPECT_EQ(sut.use_count(), 1);
    EXPECT_EQ(sut2.use_count(), 1);
}

TEST(SharedPtrsResetTakingPtrShould, setManagedPtrToNewValue) {
    my::shared_ptr<double> sut{new double};
    my::shared_ptr<DummyBase> sut2{new DummyDerived};
    ASSERT_NE(sut.get(), nullptr);
    ASSERT_NE(sut2.get(), nullptr);

    double* new_ptr_to_be_set = new double;
    DummyBase* new_ptr_to_be_set2 = new DummyDerived;

    sut.reset(new_ptr_to_be_set);
    sut2.reset(new_ptr_to_be_set2);

    EXPECT_EQ(sut.get(), new_ptr_to_be_set);
    EXPECT_EQ(sut2.get(), new_ptr_to_be_set2);
}

TEST(SharedPtrsResetTakingPtrShould, setUseCountToOneIfPtrIsNotNull) {
    my::shared_ptr<double> sut{new double};
    my::shared_ptr<double> sut_copy = sut;
    my::shared_ptr<double> sut_copy2 = sut;
    my::shared_ptr<DummyBase> sut2{new DummyDerived};
    my::shared_ptr<DummyBase> sut2_copy = sut2;
    my::shared_ptr<DummyBase> sut2_copy2 = sut2;

    ASSERT_EQ(sut.use_count(), 3);
    ASSERT_EQ(sut2.use_count(), 3);

    sut.reset(new double);
    sut2.reset(new DummyDerived);

    EXPECT_EQ(sut.use_count(), 1);
    EXPECT_EQ(sut2.use_count(), 1);
}

TEST(SharedPtrsResetTakingPtrAndDeleterShould,
     destroyPreviouslyManagedObjectAfterResetCalledWhenUseCountIsEqualToOne) {
    auto deleter = customDeleter<CustomDeletionDetectorMock>;
    my::shared_ptr<CustomDeletionDetectorMock> sut{new CustomDeletionDetectorMock, deleter};
    ASSERT_NE(sut.get(), nullptr);
    ASSERT_EQ(sut.use_count(), 1);
    EXPECT_CALL(*sut, detectCustomDeletion);

    auto new_deleter = customDeleter<CustomDeletionDetectorMock>;
    sut.reset(new CustomDeletionDetectorMock, new_deleter);

    EXPECT_CALL(*sut, detectCustomDeletion);
}

TEST(SharedPtrsResetTakingPtrAndDeleterShould, decreaseUseCountOfPreviouslyManagedPtr) {
    my::shared_ptr<double> sut{new double};
    my::shared_ptr<double> sut_copy = sut;
    my::shared_ptr<DummyBase> sut2{new DummyDerived};
    my::shared_ptr<DummyBase> sut2_copy = sut2;
    ASSERT_EQ(sut.use_count(), 2);
    ASSERT_EQ(sut2.use_count(), 2);

    sut_copy.reset(new double, customDeleter<double>);
    sut2_copy.reset(new DummyDerived, customDeleter<DummyBase>);

    EXPECT_EQ(sut.use_count(), 1);
    EXPECT_EQ(sut2.use_count(), 1);
}

TEST(SharedPtrsResetTakingPtrAndDeleterShould, setManagedPtrToNewValue) {
    // for oridinary type
    my::shared_ptr<double> sut{new double};
    ASSERT_NE(sut.get(), nullptr);

    double* new_ptr_to_be_set = new double;
    sut.reset(new_ptr_to_be_set, customDeleter<double>);

    EXPECT_EQ(sut.get(), new_ptr_to_be_set);

    // for derived types
    my::shared_ptr<DummyBase> sut2{new DummyDerived};
    ASSERT_NE(sut2.get(), nullptr);

    DummyBase* new_ptr_to_be_set2 = new DummyDerived;
    sut2.reset(new_ptr_to_be_set2, customDeleter<DummyBase>);

    EXPECT_EQ(sut2.get(), new_ptr_to_be_set2);
}

TEST(SharedPtrsResetTakingPtrAndDeleterShould, setUseCountToOneIfPtrIsNotNull) {
    my::shared_ptr<double> sut{new double};
    my::shared_ptr<double> sut_copy = sut;
    my::shared_ptr<double> sut_copy2 = sut;
    my::shared_ptr<DummyBase> sut2{new DummyDerived};
    my::shared_ptr<DummyBase> sut2_copy = sut2;
    my::shared_ptr<DummyBase> sut2_copy2 = sut2;

    ASSERT_EQ(sut.use_count(), 3);
    ASSERT_EQ(sut2.use_count(), 3);

    sut.reset(new double, customDeleter<double>);
    sut2.reset(new DummyDerived, customDeleter<DummyBase>);

    EXPECT_EQ(sut.use_count(), 1);
    EXPECT_EQ(sut2.use_count(), 1);
}

}  // namespace tests
