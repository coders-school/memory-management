#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

// TODO: VERIFY if not my namespace
namespace tests {

// constructor tests
TEST(WeakPtrShould, bePossibleToBeCratedUsingDefaultConstructor) {
    [[maybe_unused]] my::weak_ptr<int> sut{};
    [[maybe_unused]] my::weak_ptr<double> sut2{};
    [[maybe_unused]] my::weak_ptr<std::string> sut3{};
}

// TODO: VERIFY remove or refactor when ptr access after lock() available
//  TEST(WeakPtrShould, storeNullPtrAfterCreationWithDefaultConstructor) {
//      my::weak_ptr<int> sut{};
//      my::weak_ptr<double> sut2{};
//      my::weak_ptr<std::string> sut3;

//     EXPECT_EQ(sut.get(), nullptr);
//     EXPECT_EQ(sut2.get(), nullptr);
//     EXPECT_EQ(sut3.get(), nullptr);
// }

TEST(WeakPtrShould, bePossibleToBeConstructedFromSharedPtrToSameType) {
    my::shared_ptr<int> shared1(new int{20});
    my::shared_ptr<double> shared2(new double{10.0});
    my::shared_ptr<std::string> shared3(new std::string);

    [[maybe_unused]] my::weak_ptr<int> sut1{shared1};
    [[maybe_unused]] my::weak_ptr<double> sut2{shared2};
    [[maybe_unused]] my::weak_ptr<std::string> sut3{shared3};
}

// NOTE: remember about nullptr case VERIFY: maybe imposible
//  TODO: VERIFY remove or refactor when ptr access after lock() available
//  TEST(WeakPtrConstructorTakingSharedPtrShould, copyManagedPtrStoredInSharedPtr) {}

TEST(WeakPtrAfterConstructionWithSharedPtrShould, haveTheSameUseCountAsSource) {
    my::shared_ptr<int> shared(new int{20});
    my::shared_ptr<double> shared_null;
    ASSERT_EQ(shared.use_count(), 1);
    ASSERT_EQ(shared_null.use_count(), 0);

    my::weak_ptr<int> sut1{shared};
    my::weak_ptr<double> sut2{shared_null};

    EXPECT_EQ(sut1.use_count(), shared.use_count());
    EXPECT_EQ(sut2.use_count(), shared_null.use_count());
}

// NOTE: remember about nullptr case
// TODO: VERIFY remove or refactor when ptr access after lock() available
// TEST(WeakPtrConstructorTakingWeakPtrShould, copyManagedPtrStoredInSource) {}

// NOTE: remember about nullptr case
// TODO: VERIFY remove or refactor when ptr access after lock() available
// TEST(WeakPtrConstructorTakingWeakPtrShould, haveTheSameUseCountAsSource) {}

// NOTE: remember about nullptr case
// TODO: VERIFY remove or refactor when ptr access after lock() available
// TEST(WeakPtrMoveConstructorShould, copyManagedPtrStoredInSourceAndMakeSourceEmpty) {}

// TODO: VERIFY remove or refactor when ptr access after lock() available ????????????
// TEST(WeakPtrDestructorShould, decreaseWeakCountOfSharedPtrSharingControlBlock) {}

// copy assignment tests
// NOTE: remember about nullptr case
// TODO: VERIFY remove or refactor when ptr access after lock() available
// TEST(WeakPtrCopyAssignmentShould, copyManagedPtrStoredInSource) {}

// NOTE: remember about nullptr case
// TODO: VERIFY remove or refactor when ptr access after lock() available
// TEST(WeakPtrAfterCopyAssignmentShould, haveTheSameUseCountAsSource) {}

// copy assignment tests
// NOTE: remember about nullptr case
// TODO: VERIFY remove or refactor when ptr access after lock() available
// TEST(WeakPtrCopyAssignmentFromWeakPtrToConvertibleTypeShould, copyManagedPtrStoredInSource) {}

// NOTE: remember about nullptr case
// TODO: VERIFY remove or refactor when ptr access after lock() available
// TEST(WeakPtrAfterCopyAssignmentFromWeakPtrShould, haveTheSameUseCountAsSource) {}

// copy assignment tests
// NOTE: remember about nullptr case
// TODO: VERIFY remove or refactor when ptr access after lock() available
// TEST(WeakPtrCopyAssignmentFromSharedPtrToConvertibleTypeShould, copyManagedPtrStoredInSource) {}

// NOTE: remember about nullptr case
// TODO: VERIFY remove or refactor when ptr access after lock() available
// TEST(WeakPtrAfterCopyAssignmentFromSharedPtrShould, haveTheSameUseCountAsSource) {}

// move assignment tests
// NOTE: remember about nullptr case
// TODO: VERIFY remove or refactor when ptr access after lock() available
// TEST(WeakPtrMoveAssignmentShould, copyManagedPtrStoredInSourceAndMakeSourceEmpty) {}

// NOTE: remember about nullptr case
// TODO: VERIFY remove or refactor when ptr access after lock() available
// TEST(WeakPtrMoveAssignmentFromWeakPtrToConvertibleTypeShould, copyManagedPtrStoredInSourceAndMakeSourceEmpty) {}

// other functions tests
// TODO: VERIFY remove or refactor when ptr access after lock() available
// TEST(WeakPtrsResetShould, setReferencedPtrToNull) {}

TEST(WeakPtrsUseCountShould, returnNumberOfSharedPtrsOwningManagedPtr) {
    my::shared_ptr<double> shared{new double{1.0}};
    my::shared_ptr<double> shared_null{};
    my::shared_ptr<double> shared_copy{shared};
    my::shared_ptr<double> shared_null_copy{shared_null};
    ASSERT_EQ(shared.use_count(), 2);
    ASSERT_EQ(shared_null.use_count(), 0);

    my::shared_ptr<double> sut(shared);
    my::shared_ptr<double> sut_from_null(shared_null);

    EXPECT_EQ(sut.use_count(), shared.use_count());
    EXPECT_EQ(sut_from_null.use_count(), shared_null.use_count());
}

// TODO: add case when use_count drops to 0 but weak_ptr exists (after assignment done)
TEST(WeakPtrsExpired, returnTrueIfAnySharedPtrOwnsManagedPtr) {
    my::shared_ptr<int> shared{new int{1}};
    my::shared_ptr<int> shared_null{};
    ASSERT_EQ(shared.use_count(), 1);
    ASSERT_EQ(shared_null.use_count(), 0);

    my::weak_ptr<int> sut(shared);
    my::weak_ptr<int> sut_from_null(shared_null);

    EXPECT_TRUE(sut.expired());
    EXPECT_FALSE(sut_from_null.expired());
}

// TEST(WeakPtrsLockShould, returnSharedPtrToManagedObjectIfManagedPtrNotNull)
// {
//  // TODO:
// }

// TEST(WeakPtrsLockShould, returnDefaultConstructedSharedPtrIfManagedPtrIsNull)
// {
//  // TODO:
// }

}  // namespace tests