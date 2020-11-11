#include <gtest/gtest.h>

#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

constexpr size_t zeroUseCount = 0;
constexpr size_t oneUseCount = 1;
constexpr int initialValue = 5;

constexpr int expectedUseCountValueSharedPtr = 1;
constexpr int expectedUseCountValueWeakPtr = 1;
constexpr int expectedUseCountValueWeakPtrAfterMoveConstructor = 0;
constexpr int expectedUseCountValueWeakPtrAfterMoveAssignment = 0;

TEST(WeakPtrTest, CreateWeakPtrWithDefaultConstructorShouldReturnUseCount0) {
    cs::weak_ptr<int> ptr{};
    ASSERT_EQ(ptr.use_count(), zeroUseCount);
}

TEST(WeakPtrTest, WeakPtrCreateBasedOnSharedShouldReturnIncrementedUseCount) {
    cs::shared_ptr<int> sptr{new int{initialValue}};
    cs::weak_ptr<int> ptr{sptr};
    ASSERT_EQ(ptr.use_count(), oneUseCount);
}

TEST(WeakPtrTest, WeakPtrLockFunction) {
    cs::shared_ptr<int> sptr{new int{initialValue}};
    cs::weak_ptr<int> ptr{sptr};
    cs::shared_ptr<int> sptr2{ptr.lock()};

    ASSERT_EQ(sptr.get(), sptr2.get());
}

TEST(WeakPtrTest, SharedPtrCreatedFromWeakPtrShouldHaveSameValueAsOtherShared) {
    cs::shared_ptr<int> sptr{new int{initialValue}};
    cs::weak_ptr<int> ptr{sptr};
    auto sptr2 = ptr.lock();
    ASSERT_EQ(initialValue, *sptr2);
}

TEST(WeakPtrTest, WeakPtrExpireFunctionShouldReturnFalse) {
    cs::shared_ptr<int> sptr{new int{initialValue}};
    cs::weak_ptr<int> wptr{sptr};
    ASSERT_FALSE(wptr.expired());
}

TEST(WeakPtrTest, WeakPtrInitializedWithSharedAfterUseOfResetFunctionShouldBeExpired) {
    cs::shared_ptr<int> sptr{new int{initialValue}};
    cs::weak_ptr<int> ptr{sptr};
    ptr.reset();
    ASSERT_TRUE(ptr.expired());
}

TEST(WeakPtrTest, WeakPtrCopyConstructor) {
    cs::shared_ptr<int> sptr{new int{initialValue}};
    cs::weak_ptr<int> wptr1{sptr};
    cs::weak_ptr<int> wptr2{wptr1};

    ASSERT_EQ(wptr1.use_count(), expectedUseCountValueWeakPtr);
    ASSERT_EQ(wptr2.use_count(), expectedUseCountValueWeakPtr);
    ASSERT_EQ(sptr.use_count(), expectedUseCountValueSharedPtr);

    ASSERT_FALSE(wptr1.expired());
    ASSERT_FALSE(wptr2.expired());
}

TEST(WeakPtrTest, WeakPtrCopyAssignment) {
    cs::shared_ptr<int> sptr{new int{initialValue}};
    cs::weak_ptr<int> wptr1{sptr};
    cs::weak_ptr<int> wptr2{};
    wptr2 = wptr1;

    ASSERT_EQ(wptr1.use_count(), expectedUseCountValueWeakPtr);
    ASSERT_EQ(wptr2.use_count(), expectedUseCountValueWeakPtr);
    ASSERT_EQ(sptr.use_count(), expectedUseCountValueSharedPtr);

    ASSERT_FALSE(wptr1.expired());
    ASSERT_FALSE(wptr2.expired());
}

TEST(WeakPtrTest, WeakPtrMoveConstructor) {
    cs::shared_ptr<int> sptr{new int{initialValue}};
    cs::weak_ptr<int> wptr{sptr};

    ASSERT_EQ(wptr.use_count(), expectedUseCountValueWeakPtr);

    cs::weak_ptr<int> wptr2{std::move(wptr)};

    ASSERT_EQ(wptr.use_count(), expectedUseCountValueWeakPtrAfterMoveConstructor);
    ASSERT_EQ(wptr2.use_count(), expectedUseCountValueWeakPtr);
    ASSERT_EQ(sptr.use_count(), expectedUseCountValueSharedPtr);

    ASSERT_TRUE(wptr.expired());
    ASSERT_FALSE(wptr2.expired());
}

TEST(WeakPtrTest, WeakPtrMoveAssignment) {
    cs::shared_ptr<int> sptr{new int{initialValue}};
    cs::weak_ptr<int> wptr{sptr};

    ASSERT_EQ(wptr.use_count(), expectedUseCountValueWeakPtr);

    cs::weak_ptr<int> wptr2{std::move(wptr)};
    ASSERT_EQ(wptr.use_count(), expectedUseCountValueWeakPtrAfterMoveAssignment);
    ASSERT_EQ(wptr2.use_count(), expectedUseCountValueWeakPtr);
    ASSERT_EQ(sptr.use_count(), expectedUseCountValueSharedPtr);

    ASSERT_TRUE(wptr.expired());
    ASSERT_FALSE(wptr2.expired());
}
