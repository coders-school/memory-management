#include <gtest/gtest.h>

#include "WeakPtr.hpp"

constexpr int initValue = 5;
constexpr int useCounter = 1;
constexpr int zeroUseCounter = 0;

struct WeakPtrTest : public ::testing::Test {
    WeakPtrTest()
        : testWeakPtr(testSharedPtr) {}

    cs::SharedPtr<int> testSharedPtr{new int{initValue}};
    cs::WeakPtr<int> testWeakPtr;
};

TEST_F(WeakPtrTest, ShouldGetOneUseCount) {
    ASSERT_EQ(testWeakPtr.use_count(), useCounter);
    ASSERT_EQ(testWeakPtr.use_count(), testSharedPtr.use_count());
}

TEST_F(WeakPtrTest, ShouldGetZeroUseCountForResetEmptyWeakPtr) {
    cs::WeakPtr<int> emptyTestWeakPtr{};
    ASSERT_EQ(emptyTestWeakPtr.use_count(), zeroUseCounter);
}

TEST_F(WeakPtrTest, ShouldExpiredReturnFalseForValidPtr) {
    ASSERT_FALSE(testWeakPtr.expired());
}

TEST_F(WeakPtrTest, ShouldResetPtr) {
    testWeakPtr.reset();
    ASSERT_TRUE(testWeakPtr.expired());
}

TEST_F(WeakPtrTest, ShouldPtrBeCreatedByCopyCtor) {
    cs::WeakPtr<int> copyTestWeakPtr(testWeakPtr);

    ASSERT_FALSE(copyTestWeakPtr.expired());
    ASSERT_FALSE(testWeakPtr.expired());
}

TEST_F(WeakPtrTest, ShouldPtrBeCreatedByCopyAssignment) {
    cs::WeakPtr<int> copyTestWeakPtr{};
    copyTestWeakPtr = testWeakPtr;

    ASSERT_FALSE(copyTestWeakPtr.expired());
    ASSERT_FALSE(testWeakPtr.expired());
}

TEST_F(WeakPtrTest, ShouldPtrBeCreatedByMoveCtor) {
    cs::WeakPtr<int> moveTestWeakPtr{std::move(testWeakPtr)};

    ASSERT_FALSE(moveTestWeakPtr.expired());
    ASSERT_TRUE(testWeakPtr.expired());
}

TEST_F(WeakPtrTest, ShouldPtrBeCreatedByMoveAssignment) {
    cs::WeakPtr<int> moveTestWeakPtr{};
    moveTestWeakPtr = std::move(testWeakPtr);

    ASSERT_FALSE(moveTestWeakPtr.expired());
    ASSERT_TRUE(testWeakPtr.expired());
}

TEST_F(WeakPtrTest, ShouldLockTestWeakPtr) {
    cs::SharedPtr<int> lockSharedPtr{testWeakPtr.lock()};

    ASSERT_EQ(*lockSharedPtr, initValue);
    ASSERT_FALSE(testWeakPtr.expired());
}

TEST_F(WeakPtrTest, ShouldEmptyTestWeakPtrLockReturnEmptySharedPtr) {
    cs::WeakPtr<int> emptyWeakPtr{};
    cs::SharedPtr<int> lockSharedPtr{emptyWeakPtr.lock()};

    ASSERT_EQ(lockSharedPtr.get(), nullptr);
    ASSERT_FALSE(testWeakPtr.expired());
    ASSERT_TRUE(emptyWeakPtr.expired());
}