#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

// TODO: VERIFY if not my namespace
namespace tests {

class DummyBase {
public:
    virtual ~DummyBase() = default;
};

class DummyDerived : public DummyBase {};

// constructor tests
TEST(WeakPtrShould, bePossibleToBeCratedUsingDefaultConstructor) {
    [[maybe_unused]] my::weak_ptr<int> sut{};
    [[maybe_unused]] my::weak_ptr<double> sut2{};
    [[maybe_unused]] my::weak_ptr<std::string> sut3{};
}

TEST(WeakPtrShould, storeNullPtrAfterCreationWithDefaultConstructor) {
    my::weak_ptr<int> sut{};
    my::weak_ptr<double> sut2{};
    my::weak_ptr<std::string> sut3;

    // the only way to access managed ptr is to construct shared_ptr from sut
    EXPECT_EQ(my::shared_ptr<int>{sut}.get(), nullptr);
    EXPECT_EQ(my::shared_ptr<double>{sut2}.get(), nullptr);
    EXPECT_EQ(my::shared_ptr<std::string>{sut3}.get(), nullptr);
}

TEST(WeakPtrShould, bePossibleToBeConstructedFromSharedPtrToSameType) {
    my::shared_ptr<int> shared1(new int{20});
    my::shared_ptr<double> shared2(new double{10.0});
    my::shared_ptr<std::string> shared3(new std::string);

    [[maybe_unused]] my::weak_ptr<int> sut1{shared1};
    [[maybe_unused]] my::weak_ptr<double> sut2{shared2};
    [[maybe_unused]] my::weak_ptr<std::string> sut3{shared3};
}

TEST(WeakPtrShould, bePossibleToBeConstructedFromSharedPtrToConvertibleType) {
    my::shared_ptr<DummyDerived> shared(new DummyDerived);

    [[maybe_unused]] my::weak_ptr<DummyBase> sut{shared};
}

TEST(WeakPtrConstructorTakingSharedPtrShould, copyManagedPtrStoredInSharedPtr) {
    my::shared_ptr<int> shared(new int{20});
    my::shared_ptr<double> shared_null;
    ASSERT_NE(shared.get(), nullptr);
    ASSERT_EQ(shared_null.get(), nullptr);

    my::weak_ptr<int> sut_from_shared{shared};
    my::weak_ptr<double> sut_from_shared_null{shared_null};
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<int> shared_converted_back_from_sut{sut_from_shared};
    my::shared_ptr<double> shared_converted_back_from_sut_null{sut_from_shared_null};

    EXPECT_EQ(shared_converted_back_from_sut.get(), shared.get());
    EXPECT_EQ(shared_converted_back_from_sut_null.get(), shared_null.get());
}

TEST(WeakPtrAfterConstructionWithSharedPtrToConvertibleTypeShould, copyManagedPtrStoredInSharedPtr) {
    my::shared_ptr<DummyDerived> shared(new DummyDerived);
    my::shared_ptr<DummyDerived> shared_null;
    ASSERT_NE(shared.get(), nullptr);
    ASSERT_EQ(shared_null.get(), nullptr);

    my::weak_ptr<DummyBase> sut_from_shared{shared};
    my::weak_ptr<DummyBase> sut_from_shared_null{shared_null};
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<DummyBase> shared_converted_back_from_sut{sut_from_shared};
    my::shared_ptr<DummyBase> shared_converted_back_from_sut_null{sut_from_shared_null};

    EXPECT_EQ(shared_converted_back_from_sut.get(), shared.get());
    EXPECT_EQ(shared_converted_back_from_sut_null.get(), shared_null.get());
}

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

TEST(WeakPtrAfterConstructionWithSharedPtrToConvertibleTypeShould, haveTheSameUseCountAsSource) {
    my::shared_ptr<DummyDerived> shared(new DummyDerived);
    my::shared_ptr<DummyDerived> shared_null;
    ASSERT_EQ(shared.use_count(), 1);
    ASSERT_EQ(shared_null.use_count(), 0);

    my::weak_ptr<DummyBase> sut1{shared};
    my::weak_ptr<DummyBase> sut2{shared_null};

    EXPECT_EQ(sut1.use_count(), shared.use_count());
    EXPECT_EQ(sut2.use_count(), shared_null.use_count());
}

TEST(WeakPtrCopyConstructorShould, copyManagedPtrStoredInSource) {
    my::shared_ptr<int> shared(new int);
    my::weak_ptr<int> sut_from_shared{shared};

    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<int> shared_converted_from_sut{sut_from_shared};

    ASSERT_NE(shared.get(), nullptr);
    EXPECT_EQ(shared_converted_from_sut.get(), shared.get());
}

TEST(WeakPtrCopyConstructorShould, copyNullPtrStoredInSource) {
    my::shared_ptr<int> shared;
    my::weak_ptr<int> sut_from_shared{shared};

    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<int> shared_converted_from_sut{sut_from_shared};

    ASSERT_EQ(shared.get(), nullptr);
    EXPECT_EQ(shared_converted_from_sut.get(), shared.get());
}

TEST(WeakPtrCopyConstructorShould, haveTheSameUseCountAsSource) {
    my::shared_ptr<int> shared(new int);
    ASSERT_EQ(shared.use_count(), 1);
    my::shared_ptr<int> shared_null;
    ASSERT_EQ(shared_null.use_count(), 0);

    my::weak_ptr<int> sut_from_shared{shared};
    my::weak_ptr<int> sut_from_shared_null{shared_null};

    EXPECT_EQ(sut_from_shared.use_count(), shared.use_count());
    EXPECT_EQ(sut_from_shared_null.use_count(), shared_null.use_count());
}

TEST(WeakPtrCopyConstructorTakingWeakPtrToConvertibleTypeShould, copyManagedPtrStoredInSource) {
    my::shared_ptr<DummyDerived> shared(new DummyDerived);
    my::weak_ptr<DummyDerived> sut_from_shared{shared};

    my::weak_ptr<DummyBase> sut_from_sut_to_convertible{sut_from_shared};
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<DummyBase> shared_final_for_comparing{sut_from_sut_to_convertible};

    ASSERT_NE(shared.get(), nullptr);
    EXPECT_EQ(shared_final_for_comparing.get(), shared.get());
}
// TODO: VERIFY current work
TEST(WeakPtrCopyConstructorTakingWeakPtrToConvertibleTypeShould, copyNullPtrStoredInSource) {
    my::shared_ptr<DummyDerived> shared;
    my::weak_ptr<DummyDerived> sut_from_shared{shared};

    my::weak_ptr<DummyBase> sut_from_sut_to_convertible{sut_from_shared};
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<DummyBase> shared_final_for_comparing{sut_from_sut_to_convertible};

    ASSERT_EQ(shared.get(), nullptr);
    EXPECT_EQ(shared_final_for_comparing.get(), shared.get());
}
// TODO: VERIFY current work
TEST(WeakPtrCopyConstructorTakingWeakPtrToConvertibleTypeShould, haveTheSameUseCountAsSource) {
    my::shared_ptr<DummyDerived> shared(new DummyDerived);
    ASSERT_EQ(shared.use_count(), 1);
    my::shared_ptr<DummyDerived> shared_null;
    ASSERT_EQ(shared_null.use_count(), 0);

    my::weak_ptr<DummyBase> sut_from_shared{shared};
    my::weak_ptr<DummyBase> sut_from_shared_null{shared_null};

    EXPECT_EQ(sut_from_shared.use_count(), shared.use_count());
    EXPECT_EQ(sut_from_shared_null.use_count(), shared_null.use_count());
}

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

    EXPECT_FALSE(sut.expired());
    EXPECT_TRUE(sut_from_null.expired());
}

// TEST(WeakPtrsLockShould, returnSharedPtrToManagedObjectIfManagedPtrNotNull) {
//     my::shared_ptr<int> shared(new int);
//     ASSERT_EQ(shared.use_count(), 1);

//     my::weak_ptr<int> sut = shared;
//     my::shared_ptr<int> shared_from_lock = sut.lock();

//     EXPECT_EQ(*shared_from_lock, *shared);
//     EXPECT_EQ(shared_from_lock.use_count(), shared.use_count());
// }

// TEST(WeakPtrsLockShould, returnDefaultConstructedSharedPtrIfManagedPtrIsNull)
// {
//  // TODO:
// }

}  // namespace tests