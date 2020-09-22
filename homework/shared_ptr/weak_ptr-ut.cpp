#include <gtest/gtest.h>

#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

constexpr size_t zeroUseCount = 0;
constexpr size_t oneUseCount = 1;

constexpr int initialValue = 5;

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
    auto isShared = [&sptr2]() { return typeid(sptr2) == typeid(cs::shared_ptr<int>); }();
    ASSERT_TRUE(isShared);
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

TEST(WeakPtrTest, WeakPtrInitializedWithSharedAfterUseOfResetFunctionShouldDecrementUserCount) {
    cs::shared_ptr<int> sptr{new int{initialValue}};
    cs::weak_ptr<int> ptr{sptr};
    ptr.reset();
    ASSERT_TRUE(ptr.expired());
}

TEST(WeakPtrTest, WeakPtrMoveConstructor) {
    cs::shared_ptr<int> sptr{new int{initialValue}};
    cs::weak_ptr<int> wptr{sptr};
    cs::weak_ptr<int> wptr2{std::move(wptr)};
    ASSERT_TRUE(wptr.expired());
    ASSERT_FALSE(wptr2.expired());
}

TEST(WeakPtrTest, WeakPtrMoveAssignment) {
    cs::shared_ptr<int> sptr{new int{initialValue}};
    cs::weak_ptr<int> wptr{sptr};
    cs::weak_ptr<int> wptr2{};
    wptr2 = std::move(wptr);
    ASSERT_TRUE(wptr.expired());
    ASSERT_FALSE(wptr2.expired());
}