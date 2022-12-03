#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"


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

TEST(WeakPtrCopyConstructorTakingWeakPtrToConvertibleTypeShould, copyNullPtrStoredInSource) {
    my::shared_ptr<DummyDerived> shared;
    my::weak_ptr<DummyDerived> sut_from_shared{shared};

    my::weak_ptr<DummyBase> sut_from_sut_to_convertible{sut_from_shared};
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<DummyBase> shared_final_for_comparing{sut_from_sut_to_convertible};

    ASSERT_EQ(shared.get(), nullptr);
    EXPECT_EQ(shared_final_for_comparing.get(), shared.get());
}

TEST(WeakPtrCopyConstructorTakingWeakPtrToConvertibleTypeShould, haveTheSameUseCountAsSource) {
    my::shared_ptr<DummyDerived> shared(new DummyDerived);
    ASSERT_EQ(shared.use_count(), 1);
    my::shared_ptr<DummyDerived> shared_null;
    ASSERT_EQ(shared_null.use_count(), 0);
    my::weak_ptr<DummyDerived> sut_from_shared{shared};
    my::weak_ptr<DummyDerived> sut_from_shared_null{shared_null};

    my::weak_ptr<DummyBase> sut_from_sut_to_convertible{sut_from_shared};
    my::weak_ptr<DummyBase> sut_from_sut_null_to_convertible{sut_from_shared_null};
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<DummyBase> shared_final_for_comparing{sut_from_sut_to_convertible};
    my::shared_ptr<DummyBase> shared_null_final_for_comparing{sut_from_sut_null_to_convertible};

    EXPECT_EQ(shared_final_for_comparing.use_count(), shared.use_count());
    EXPECT_EQ(shared_null_final_for_comparing.use_count(), shared_null.use_count());
}

TEST(WeakPtrMoveConstructorShould, copyManagedPtrStoredInSource) {
    my::shared_ptr<float> shared_original{new float};
    ASSERT_NE(shared_original.get(), nullptr);
    my::weak_ptr<float> sut_from_original{shared_original};

    my::weak_ptr<float> sut_from_moved{std::move(sut_from_original)};
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<float> shared_final_to_compare{sut_from_moved};

    EXPECT_EQ(shared_final_to_compare.get(), shared_original.get());
}

TEST(WeakPtrMoveConstructorShould, setManagedPtrStoredInSourceToNullptr) {
    my::shared_ptr<float> shared_original{new float};
    ASSERT_NE(shared_original.get(), nullptr);
    my::weak_ptr<float> sut_to_be_moved{shared_original};

    my::weak_ptr<float> sut_from_moved{std::move(sut_to_be_moved)};
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<float> shared_final_to_compare{sut_to_be_moved};

    EXPECT_EQ(shared_final_to_compare.get(), nullptr);
}

TEST(WeakPtrMoveConstructorShould, takeOverUseCountFromSource) {
    my::shared_ptr<float> shared_original{new float};
    ASSERT_EQ(shared_original.use_count(), 1);
    my::weak_ptr<float> sut_to_be_moved{shared_original};

    my::weak_ptr<float> sut_from_moved{std::move(sut_to_be_moved)};

    EXPECT_EQ(sut_from_moved.use_count(), 1);
    EXPECT_EQ(sut_to_be_moved.use_count(), 0);
}

TEST(WeakPtrMoveConstructorTakingWeakPtrToConvertibleTypeShould,
     copyManagedPtrStoredInSource) {
    my::shared_ptr<DummyDerived> shared_original{new DummyDerived};
    ASSERT_NE(shared_original.get(), nullptr);
    my::weak_ptr<DummyDerived> sut_from_original{shared_original};

    my::weak_ptr<DummyBase> sut_from_moved{std::move(sut_from_original)};
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<DummyBase> shared_final_to_compare{sut_from_moved};

    EXPECT_EQ(shared_final_to_compare.get(), shared_original.get());
}

TEST(WeakPtrMoveConstructorTakingWeakPtrToConvertibleTypeShould,
     setManagedPtrStoredInSourceToNullptr) {
    my::shared_ptr<DummyDerived> shared_original{new DummyDerived};
    ASSERT_NE(shared_original.get(), nullptr);
    my::weak_ptr<DummyDerived> sut_to_be_moved{shared_original};

    my::weak_ptr<DummyBase> sut_from_moved{std::move(sut_to_be_moved)};
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<DummyBase> shared_final_to_compare{sut_to_be_moved};

    EXPECT_EQ(shared_final_to_compare.get(), nullptr);
}

TEST(WeakPtrMoveConstructorTakingWeakPtrToConvertibleTypeShould,
     takeOverUseCountFromSource) {
    my::shared_ptr<DummyDerived> shared_original{new DummyDerived};
    ASSERT_EQ(shared_original.use_count(), 1);
    my::weak_ptr<DummyDerived> sut_to_be_moved{shared_original};

    my::weak_ptr<DummyBase> sut_from_moved{std::move(sut_to_be_moved)};

    EXPECT_EQ(sut_from_moved.use_count(), 1);
    EXPECT_EQ(sut_to_be_moved.use_count(), 0);
}

// copy assignment tests
TEST(WeakPtrCopyAssignmentShould, copyManagedPtrStoredInSource) {
    my::shared_ptr<double> shared(new double);
    my::weak_ptr<double> sut_to_be_copied(shared);

    my::weak_ptr<double> sut;
    sut = sut_to_be_copied;
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<double> shared_final_to_compare{sut};

    ASSERT_NE(shared.get(), nullptr);
    EXPECT_EQ(shared.get(), shared_final_to_compare.get());
}

TEST(WeakPtrAfterCopyAssignmentShould, haveTheSameUseCountAsSource) {
    my::shared_ptr<double> shared(new double);
    ASSERT_EQ(shared.use_count(), 1);
    my::weak_ptr<double> sut_to_be_copied(shared);

    my::weak_ptr<double> sut;
    sut = sut_to_be_copied;
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<double> shared_final_to_compare{sut};

    ASSERT_EQ(shared.use_count(), 2);
    EXPECT_EQ(shared.use_count(), shared_final_to_compare.use_count());
}

TEST(WeakPtrCopyAssignmentTakingToWeakPtrToConvertibleTypeShould, copyManagedPtrStoredInSource) {
    my::shared_ptr<DummyDerived> shared(new DummyDerived);
    my::weak_ptr<DummyDerived> sut_to_be_copied(shared);

    my::weak_ptr<DummyBase> sut;
    sut = sut_to_be_copied;
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<DummyBase> shared_final_to_compare{sut};

    ASSERT_NE(shared.get(), nullptr);
    EXPECT_EQ(shared.get(), shared_final_to_compare.get());
}

TEST(WeakPtrCopyAssignmentTakingToWeakPtrToConvertibleTypeShould, haveTheSameUseCountAsSource) {
    my::shared_ptr<DummyDerived> shared(new DummyDerived);
    ASSERT_EQ(shared.use_count(), 1);
    my::weak_ptr<DummyDerived> sut_to_be_copied(shared);

    my::weak_ptr<DummyBase> sut;
    sut = sut_to_be_copied;
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<DummyBase> shared_final_to_compare{sut};

    ASSERT_EQ(shared.use_count(), 2);
    EXPECT_EQ(shared.use_count(), shared_final_to_compare.use_count());
}

TEST(WeakPtrCopyAssignmentTakingSharedPtrToSameTypeShould, copyManagedPtrStoredInSource) {
    my::shared_ptr<float> shared(new float);
    my::shared_ptr<float> shared_null;

    my::weak_ptr<float> sut;
    sut = shared;
    my::weak_ptr<float> sut_from_null;
    sut_from_null = shared_null;
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<float> shared_final_to_compare{sut};
    my::shared_ptr<float> shared_final_to_compare_form_null{sut_from_null};

    ASSERT_NE(shared.get(), nullptr);
    ASSERT_EQ(shared_null.get(), nullptr);
    EXPECT_EQ(shared.get(), shared_final_to_compare.get());
    EXPECT_EQ(shared_null.get(), shared_final_to_compare_form_null.get());
}

TEST(WeakPtrCopyAssignmentTakingSharedPtrToConvertibleTypeShould, copyManagedPtrStoredInSource) {
    my::shared_ptr<DummyDerived> shared(new DummyDerived);
    my::shared_ptr<DummyDerived> shared_null;

    my::weak_ptr<DummyBase> sut;
    sut = shared;
    my::weak_ptr<DummyBase> sut_from_null;
    sut_from_null = shared_null;
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<DummyBase> shared_final_to_compare{sut};
    my::shared_ptr<DummyBase> shared_final_to_compare_form_null{sut_from_null};

    ASSERT_NE(shared.get(), nullptr);
    ASSERT_EQ(shared_null.get(), nullptr);
    EXPECT_EQ(shared.get(), shared_final_to_compare.get());
    EXPECT_EQ(shared_null.get(), shared_final_to_compare_form_null.get());
}

TEST(WeakPtrCopyAssignmentTakingSharedPtrToSameTypeShould, haveTheSameUseCountAsSource) {
    my::shared_ptr<float> shared(new float);
    my::shared_ptr<float> shared_null;
    ASSERT_EQ(shared.use_count(), 1);
    ASSERT_EQ(shared_null.use_count(), 0);

    my::weak_ptr<float> sut;
    sut = shared;
    my::weak_ptr<float> sut_from_null;
    sut_from_null = shared_null;
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<float> shared_final_to_compare{sut};
    my::shared_ptr<float> shared_final_to_compare_form_null{sut_from_null};

    EXPECT_EQ(shared.use_count(), shared_final_to_compare.use_count());
    EXPECT_EQ(shared_null.use_count(), shared_final_to_compare_form_null.use_count());
}

TEST(WeakPtrCopyAssignmentTakingSharedPtrToConvertibleTypeShould, haveTheSameUseCountAsSource) {
    my::shared_ptr<DummyDerived> shared(new DummyDerived);
    my::shared_ptr<DummyDerived> shared_null;
    ASSERT_EQ(shared.use_count(), 1);
    ASSERT_EQ(shared_null.use_count(), 0);

    my::weak_ptr<DummyBase> sut;
    sut = shared;
    my::weak_ptr<DummyBase> sut_from_null;
    sut_from_null = shared_null;
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<DummyBase> shared_final_to_compare{sut};
    my::shared_ptr<DummyBase> shared_final_to_compare_form_null{sut_from_null};

    EXPECT_EQ(shared.use_count(), shared_final_to_compare.use_count());
    EXPECT_EQ(shared_null.use_count(), shared_final_to_compare_form_null.use_count());
}

TEST(WeakPtrMoveAssignmentTakingWeakPtrToSameTypeShould, copyManagedPtrStoredInSource) {
    my::shared_ptr<float> shared(new float);
    my::weak_ptr<float> sut_for_moving{shared};

    my::weak_ptr<float> sut;
    sut = std::move(sut_for_moving);
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<float> shared_final_to_compare{sut};

    ASSERT_NE(shared.get(), nullptr);
    EXPECT_EQ(shared.get(), shared_final_to_compare.get());
}

TEST(WeakPtrMoveAssignmentTakingWeakPtrToSameTypeShould, setManagedPtrStoredInSourceToNullptr) {
    my::shared_ptr<float> shared(new float);
    my::weak_ptr<float> sut_for_moving{shared};

    my::weak_ptr<float> sut;
    sut = std::move(sut_for_moving);
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<float> shared_final_from_moved{sut_for_moving};

    ASSERT_NE(shared.get(), nullptr);
    EXPECT_EQ(shared_final_from_moved.get(), nullptr);
}

TEST(WeakPtrMoveAssignmentTakingWeakPtrToSameTypeShould, takeOverUseCountFromSource) {
    my::shared_ptr<float> shared(new float);
    // make copy of shared just to set the use_count to 2
    my::shared_ptr<float> shared_copy{shared};
    my::weak_ptr<float> sut_for_moving{shared};

    my::weak_ptr<float> sut;
    sut = std::move(sut_for_moving);

    ASSERT_EQ(shared.use_count(), 2);
    EXPECT_EQ(sut.use_count(), 2);
    EXPECT_EQ(sut_for_moving.use_count(), 0);
}

TEST(WeakPtrMoveAssignmentTakingWeakPtrToConvertibleTypeShould, copyManagedPtrStoredInSource) {
    my::shared_ptr<DummyDerived> shared(new DummyDerived);
    my::weak_ptr<DummyDerived> sut_for_moving{shared};

    my::weak_ptr<DummyBase> sut;
    sut = std::move(sut_for_moving);
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<DummyBase> shared_final_to_compare{sut};

    ASSERT_NE(shared.get(), nullptr);
    EXPECT_EQ(shared.get(), shared_final_to_compare.get());
}

TEST(WeakPtrMoveAssignmentTakingWeakPtrToConvertibleTypeShould, setManagedPtrStoredInSourceToNullptr) {
    my::shared_ptr<DummyDerived> shared(new DummyDerived);
    my::weak_ptr<DummyDerived> sut_for_moving{shared};

    my::weak_ptr<DummyBase> sut;
    sut = std::move(sut_for_moving);
    // the only way to access managed ptr is to construct shared_ptr from sut
    my::shared_ptr<DummyBase> shared_final_from_moved{sut_for_moving};

    ASSERT_NE(shared.get(), nullptr);
    EXPECT_EQ(shared_final_from_moved.get(), nullptr);
}

TEST(WeakPtrMoveAssignmentTakingWeakPtrToConvertibleTypeShould, takeOverUseCountFromSource) {
    my::shared_ptr<DummyDerived> shared(new DummyDerived);
    // make copy of shared just to set the use_count to 2
    my::shared_ptr<DummyDerived> shared_copy{shared};
    my::weak_ptr<DummyDerived> sut_for_moving{shared};

    my::weak_ptr<DummyBase> sut;
    sut = std::move(sut_for_moving);

    ASSERT_EQ(shared.use_count(), 2);
    EXPECT_EQ(sut.use_count(), 2);
    EXPECT_EQ(sut_for_moving.use_count(), 0);
}

// other functions tests
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

TEST(WeakPtrsExpired, returnTrueAfterWeakPtrExistsAfterAllSharedPtrsDestroyed) {
    my::weak_ptr<double> sut;
    {
        my::shared_ptr<double> shared(new double);
        sut = shared;
        EXPECT_FALSE(sut.expired());
    }

    EXPECT_TRUE(sut.expired());
}

TEST(WeakPtrsLockShould, createSharedPtrToManagedObjectIfNotExpired) {
    my::shared_ptr<int> shared(new int{20});
    ASSERT_EQ(shared.use_count(), 1);
    my::weak_ptr<int> sut = shared;

    my::shared_ptr<int> shared_from_lock = sut.lock();

    EXPECT_NE(shared_from_lock.get(), nullptr);
    EXPECT_EQ(shared_from_lock.use_count(), 2);
    EXPECT_EQ(*shared_from_lock, *shared);
    EXPECT_EQ(shared_from_lock.use_count(), shared.use_count());
}

TEST(WeakPtrsLockShould, returnDefaultConstructedSharedPtrIfManagedPtrIsNull) {
    my::shared_ptr<int> shared;
    ASSERT_EQ(shared.use_count(), 0);
    ASSERT_EQ(shared.get(), nullptr);
    my::weak_ptr<int> sut = shared;
    ASSERT_TRUE(sut.expired());

    my::shared_ptr<int> shared_from_lock = sut.lock();

    EXPECT_EQ(shared_from_lock.get(), nullptr);
    EXPECT_EQ(shared_from_lock.use_count(), 0);
}

TEST(WeakPtrsResetShould, setManagedPtrToNullptr) {
    my::shared_ptr<int> shared{new int};
    my::weak_ptr<int> sut{shared};
    // the only way to access managed ptr is to construct shared_ptr from sut
    auto shared_from_sut_before_reset = sut.lock();

    sut.reset();

    auto shared_from_sut_after_reset = sut.lock();

    ASSERT_NE(shared.get(), nullptr);
    ASSERT_NE(shared_from_sut_before_reset.get(), nullptr);
    EXPECT_EQ(shared_from_sut_after_reset.get(), nullptr);
}
