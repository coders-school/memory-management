#include "weak.hpp"

#include <gtest/gtest.h>

class WeakTest : public ::testing::Test {
    public:
    int defaultValue{5};
    int anotherValue{10};
    cs::shared_ptr<int> defaultShared{new int{defaultValue}};
    cs::shared_ptr<int> anotherShared{new int{anotherValue}};

};

TEST_F(WeakTest, canBeDefaultCreated) {
    cs::weak_ptr<int> ptr{};
}

TEST_F(WeakTest, canBeCreatedFromSharedPtr) {
    cs::weak_ptr<int> ptr{defaultShared};
}

TEST_F(WeakTest, expiredShouldBeFalseWhenNotDangling) {
    cs::weak_ptr<int> ptr{defaultShared};
    EXPECT_FALSE(ptr.expired());
}

TEST_F(WeakTest, expiredShouldBeTrueWhenDangling) {
    cs::weak_ptr<int> ptr{defaultShared};
    defaultShared.reset();
    EXPECT_TRUE(ptr.expired());
}

TEST_F(WeakTest, useCountShouldReturnTheNumberOfSharedReferences) {
    cs::weak_ptr<int> ptr{defaultShared};
    int expectedUseCount{1};
    EXPECT_EQ(ptr.use_count(), defaultShared.use_count());
    EXPECT_EQ(ptr.use_count(), expectedUseCount);
    EXPECT_EQ(defaultShared.use_count(), expectedUseCount);
}

TEST_F(WeakTest, useCountShouldReturn0WhenNoSharedManagesObject) {
    cs::weak_ptr<int> ptr{defaultShared};
    int expectedUseCount{0};
    defaultShared.reset();
    EXPECT_EQ(ptr.use_count(), defaultShared.use_count());
    EXPECT_EQ(ptr.use_count(), expectedUseCount);
    EXPECT_EQ(defaultShared.use_count(), expectedUseCount);
}

TEST_F(WeakTest, resetShouldReleaseReferenceToManagedObject) {
    cs::weak_ptr<int> ptr{defaultShared};
    ptr.reset();
    int expectedWeakPtrUseCount{0};
    int expectedSharedPtrUseCount{1};
    EXPECT_EQ(ptr.use_count(), expectedWeakPtrUseCount);
    EXPECT_EQ(defaultShared.use_count(), expectedSharedPtrUseCount);
}

TEST_F(WeakTest, lockShouldReturnNullptrWhenNoManagedObject) {
    cs::weak_ptr<int> ptr{defaultShared};
    ptr.reset();
    EXPECT_EQ(ptr.lock().get(), nullptr);
}

TEST_F(WeakTest, lockShouldReturnSharedPtrWhenIsManagedObject) {
    cs::weak_ptr<int> ptr{defaultShared};
    EXPECT_EQ(ptr.lock(), defaultShared);
}

TEST_F(WeakTest, lockShouldReturnNullPtrAfterWeakPtrReset) {
    cs::weak_ptr<int> ptr{defaultShared};
    ptr.reset();
    EXPECT_EQ(ptr.lock().get(), nullptr);
}

TEST_F(WeakTest, copyAssignmentShouldIncreaseWeakRefCount) {
    cs::weak_ptr<int> ptr1{defaultShared};
    cs::weak_ptr<int> ptr2;
    ptr2 = ptr1;
    ptr1.reset();
    EXPECT_EQ(ptr2.lock(), defaultShared);
}

TEST_F(WeakTest, copyAssignmentShouldReleaseMemoryWhenSharedRefIs0) {
    cs::weak_ptr<int> ptr1{defaultShared};
    cs::weak_ptr<int> ptr2{anotherShared};
    anotherShared.reset();
    ptr2 = ptr1;
    EXPECT_EQ(ptr2.lock(), ptr1.lock());
    EXPECT_EQ(ptr2.lock(), defaultShared);
}

TEST_F(WeakTest, moveAssignmentShouldMoveDataAndDecreaseRefCount) {
    cs::weak_ptr<int> ptr1{defaultShared};
    cs::weak_ptr<int> ptr2{anotherShared};
    ptr2 = std::move(ptr1);
    EXPECT_EQ(ptr2.lock(), defaultShared);
}

TEST_F(WeakTest, moveConstructorShouldMoveDataAndDecreaseRefCount) {
    cs::weak_ptr<int> ptr1{cs::weak_ptr<int>{defaultShared}};
    EXPECT_EQ(ptr1.lock(), defaultShared);
    cs::weak_ptr<int> ptr2{std::move(ptr1)};
    EXPECT_EQ(ptr2.lock(), defaultShared);
}

TEST_F(WeakTest, weakCanBeCopiedFromSharedPtr) {
    cs::weak_ptr<int> ptr;
    ptr = defaultShared;
    EXPECT_EQ(ptr.lock(), defaultShared);
}

TEST_F(WeakTest, weakWhenCopiedShouldReleaseMemoryWhenIsTheLastWeakPtrAndSharedCountIs0) {
    cs::weak_ptr<int> ptr{defaultShared};
    defaultShared.reset();
    ptr = anotherShared;
    EXPECT_EQ(ptr.lock(), anotherShared);
}

TEST_F(WeakTest, weakWhenCopiedFromEmptySharedPtrShouldBeEmpty) {
    cs::shared_ptr<int> emptyShared{};
    cs::weak_ptr<int> emptyWeak{};
    emptyWeak = emptyShared;
    EXPECT_EQ(emptyWeak.lock().get(), nullptr);
}

TEST_F(WeakTest, weakWhenCopiedFromEmptyWeakPtrShouldBeEmpty) {
    cs::weak_ptr<int> emptyWeak1{};
    cs::weak_ptr<int> emptyWeak2{};
    emptyWeak1 = emptyWeak2;
    EXPECT_EQ(emptyWeak1.lock().get(), nullptr);
}
