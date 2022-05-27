#include <gtest/gtest.h>

#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

constexpr size_t zeroUseCount = 0;
constexpr size_t oneUseCount = 1;

constexpr int initialValue = 5;

TEST(WeakPtrTest, CreateWeakPtrWithDefaultConstructorShouldReturnUseCount0) {
    my::weak_ptr<int> ptr{};
    ASSERT_EQ(ptr.use_count(), zeroUseCount);
}

TEST(WeakPtrTest, WeakPtrCreateBasedOnSharedShouldReturnIncrementedUseCount) {
    my::shared_ptr<int> sptr{new int{initialValue}};
    my::weak_ptr<int> ptr{sptr};
    ASSERT_EQ(ptr.use_count(), oneUseCount);
}

TEST(WeakPtrTest, WeakPtrLockFunction) {
    my::shared_ptr<int> sptr{new int{initialValue}};
    my::weak_ptr<int> ptr{sptr};
    my::shared_ptr<int> sptr2{ptr.lock()};

    ASSERT_EQ(sptr.get(), sptr2.get());
}

TEST(WeakPtrTest, SharedPtrCreatedFromWeakPtrShouldHaveSameValueAsOtherShared) {
    my::shared_ptr<int> sptr{new int{initialValue}};
    my::weak_ptr<int> ptr{sptr};
    auto sptr2 = ptr.lock();
    ASSERT_EQ(initialValue, *sptr2);
}

TEST(WeakPtrTest, WeakPtrExpireFunctionShouldReturnFalse) {
    my::shared_ptr<int> sptr{new int{initialValue}};
    my::weak_ptr<int> wptr{sptr};
    ASSERT_FALSE(wptr.expired());
}

TEST(WeakPtrTest, WeakPtrInitializedWithSharedAfterUseOfResetFunctionShouldBeExpired) {
    my::shared_ptr<int> sptr{new int{initialValue}};
    my::weak_ptr<int> ptr{sptr};
    ptr.reset();
    ASSERT_TRUE(ptr.expired());
}

TEST(WeakPtrTest, WeakPtrMoveConstructor) {
    constexpr int expectedUseCountValueSharedPtr = 1;
    constexpr int expectedUseCountValueWeakPtr = 1;
    constexpr int expectedUseCountValueWeakPtrAfterMoveConstructor = 0;

    my::shared_ptr<int> sptr{new int{initialValue}};
    my::weak_ptr<int> wptr{sptr};

    ASSERT_EQ(wptr.use_count(), expectedUseCountValueWeakPtr);

    my::weak_ptr<int> wptr2{std::move(wptr)};

    ASSERT_EQ(wptr.use_count(), expectedUseCountValueWeakPtrAfterMoveConstructor);
    ASSERT_EQ(wptr2.use_count(), expectedUseCountValueWeakPtr);
    ASSERT_EQ(sptr.use_count(), expectedUseCountValueSharedPtr);

    ASSERT_TRUE(wptr.expired());
    ASSERT_FALSE(wptr2.expired());
}

TEST(WeakPtrTest, WeakPtrMoveAssignment) {
    constexpr int expectedUseCountValueSharedPtr = 1;
    constexpr int expectedUseCountValueWeakPtr = 1;
    constexpr int expectedUseCountValueWeakPtrAfterMoveAssignment = 0;

    my::shared_ptr<int> sptr{new int{initialValue}};
    my::weak_ptr<int> wptr{sptr};

    ASSERT_EQ(wptr.use_count(), expectedUseCountValueWeakPtr);

    my::weak_ptr<int> wptr2{};
    wptr2 = std::move(wptr);

    ASSERT_EQ(wptr.use_count(), expectedUseCountValueWeakPtrAfterMoveAssignment);
    ASSERT_EQ(wptr2.use_count(), expectedUseCountValueWeakPtr);
    ASSERT_EQ(sptr.use_count(), expectedUseCountValueSharedPtr);

    ASSERT_TRUE(wptr.expired());
    ASSERT_FALSE(wptr2.expired());
}
