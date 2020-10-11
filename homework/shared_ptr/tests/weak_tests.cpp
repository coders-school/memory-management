#include "weak.hpp"

#include <gtest/gtest.h>

class WeakTest : public ::testing::Test {
    public:
    int defaultValue{5};
    int anotherValue{10};
    cs::shared_ptr<int> defaultShared{new int{defaultValue}};
};

TEST_F(WeakTest, canBeDefaultCreated) {
    cs::weak_ptr<int> ptr{};
}

TEST_F(WeakTest, canBeCreatedFromSharedPtr) {
    cs::weak_ptr<int> ptr{defaultShared};
}

TEST_F(WeakTest, expiredShouldBeFalseWhenNotDangling) {
    cs::weak_ptr<int> ptr{defaultShared};
    EXPECT_EQ(ptr.expired(), false);
}

TEST_F(WeakTest, expiredShouldBeTrueWhenDangling) {
    cs::weak_ptr<int> ptr{defaultShared};
    defaultShared.reset();
    EXPECT_EQ(ptr.expired(), true);
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
