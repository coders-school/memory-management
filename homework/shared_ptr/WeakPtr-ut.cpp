#include <gtest/gtest.h>

#include "SharedPtr.hpp"
#include "WeakPtr.hpp"

namespace WeakPtrTestConst {
constexpr size_t zeroUseCount = 0;
constexpr size_t oneUseCount = 1;
constexpr size_t twoUseCount = 2;
constexpr int intValue = 42;
}  // namespace WeakPtrTestConst

TEST(WeakPtrTest, EmptyWeakPtrShouldReturnUseCounterZero) {
    cs::WeakPtr<int> weakPtr{};
    ASSERT_EQ(weakPtr.use_count(), WeakPtrTestConst::zeroUseCount);
}

TEST(WeakPtrTest, WeakPtrInitiatedWithSharedPtrShouldReturnCounterEqualOne) {
    cs::SharedPtr<int> sharedPtr{new int{WeakPtrTestConst::intValue}};
    cs::WeakPtr<int> weakPtr{sharedPtr};
    ASSERT_EQ(weakPtr.use_count(), WeakPtrTestConst::oneUseCount);
}

TEST(WeakPtrTest, weakPtrShoulGetSharedPtrWithLockFunction) {
    cs::SharedPtr<int> sharedPtr{new int{WeakPtrTestConst::intValue}};
    cs::WeakPtr<int> weakPtr{sharedPtr};
    cs::SharedPtr<int> sharedPtr2{weakPtr.lock()};
    auto isShared = [&sharedPtr2]() { return typeid(sharedPtr2) == typeid(cs::SharedPtr<int>); }();
    ASSERT_TRUE(isShared);
    ASSERT_EQ(sharedPtr.get(), sharedPtr2.get());
    ASSERT_EQ(*sharedPtr, *sharedPtr2);
}

TEST(WeakPtrTest, IfGetSharedPtrFromWeakTheirValueShouldBeTheSame) {
    cs::SharedPtr<int> sharedPtr{new int{WeakPtrTestConst::intValue}};
    cs::WeakPtr<int> weakPtr{sharedPtr};
    auto sharedPtr2 = weakPtr.lock();
    ASSERT_EQ(WeakPtrTestConst::intValue, *sharedPtr2);
}

TEST(WeakPtrTest, ExpireFunctionShouldReturnFalseIfSharedPtrAlreadyExist) {
    cs::SharedPtr<int> sharedPtr{new int{WeakPtrTestConst::intValue}};
    cs::WeakPtr<int> weakPtr{sharedPtr};
    ASSERT_FALSE(weakPtr.expired());
}

TEST(WeakPtrTest, ResetFunctionShouldDecrementCounter) {
    cs::SharedPtr<int> sharedPtr{new int{WeakPtrTestConst::intValue}};
    cs::WeakPtr<int> weakPtr{sharedPtr};
    ASSERT_FALSE(weakPtr.expired());
    weakPtr.reset();
    ASSERT_TRUE(weakPtr.expired());
}

TEST(WeakPtrTest, WeakPtrMoveConstructor) {
    cs::SharedPtr<int> sharedPtr{new int{WeakPtrTestConst::intValue}};
    cs::WeakPtr<int> weakPtr{sharedPtr};
    cs::WeakPtr<int> weakPtr2{std::move(weakPtr)};
    ASSERT_TRUE(weakPtr.expired());
    ASSERT_FALSE(weakPtr2.expired());
}

TEST(WeakPtrTest, WeakPtrMoveAssignment) {
    cs::SharedPtr<int> sharedPtr{new int{WeakPtrTestConst::intValue}};
    cs::WeakPtr<int> weakPtr{sharedPtr};
    cs::WeakPtr<int> weakPtr2{};
    weakPtr2 = std::move(weakPtr);
    ASSERT_TRUE(weakPtr.expired());
    ASSERT_FALSE(weakPtr2.expired());
}

TEST(WeakPtrTest, WeakPtrCopyAssignment) {
    cs::SharedPtr<int> sharedPtr{new int{WeakPtrTestConst::intValue}};
    cs::WeakPtr<int> weakPtr{sharedPtr};
    cs::WeakPtr<int> weakPtr2 = weakPtr;
    ASSERT_FALSE(weakPtr.expired());
    ASSERT_FALSE(weakPtr2.expired());
    ASSERT_EQ(*(weakPtr.lock()), *(weakPtr2.lock()));
}

TEST(WeakPtrTest, weakPtrShouldExpireAndReleaseResourceWhenSharedPtrIsNotExist) {
    cs::SharedPtr<int> sharedPtr{new int{WeakPtrTestConst::intValue}};
    cs::WeakPtr<int> weakPtr{sharedPtr};
    auto sharedPtr2 = weakPtr.lock();
    ASSERT_EQ(sharedPtr2.use_count(), WeakPtrTestConst::twoUseCount);
    sharedPtr.reset();
    ASSERT_EQ(sharedPtr.use_count(), WeakPtrTestConst::zeroUseCount);
    ASSERT_EQ(weakPtr.use_count(), WeakPtrTestConst::oneUseCount);
    ASSERT_EQ(sharedPtr2.use_count(), WeakPtrTestConst::oneUseCount);
    sharedPtr2.reset();
    ASSERT_EQ(sharedPtr2.use_count(), WeakPtrTestConst::zeroUseCount);
    ASSERT_EQ(weakPtr.use_count(), WeakPtrTestConst::zeroUseCount);
    auto sharedPtr3 = weakPtr.lock();
    ASSERT_FALSE(sharedPtr3);
    ASSERT_TRUE(weakPtr.expired());
}
