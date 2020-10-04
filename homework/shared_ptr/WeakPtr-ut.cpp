#include <gtest/gtest.h>

#include "WeakPtr.hpp"

constexpr int initValue = 5;
constexpr int useCounter = 1;
constexpr int zeroUseCounter = 0;

struct WeakPtrTest : public ::testing::Test {
    WeakPtrTest()
        : testWeakPtr(testSharedPtr) {}

    SharedPtr<int> testSharedPtr{new int{initValue}};
    WeakPtr<int> testWeakPtr;
};

TEST_F(WeakPtrTest, ShouldGetOneUseCount) {
    ASSERT_EQ(testWeakPtr.use_count(), useCounter);
    ASSERT_EQ(testWeakPtr.use_count(), testSharedPtr.use_count());
}

TEST_F(WeakPtrTest, ShouldGetZeroUseCountForResetEmptyWeakPtr) {
    WeakPtr<int> emptyTestWeakPtr{};
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
    WeakPtr<int> copyTestWeakPtr(testWeakPtr);

    ASSERT_FALSE(copyTestWeakPtr.expired());
    ASSERT_FALSE(testWeakPtr.expired());
}

TEST_F(WeakPtrTest, ShouldPtrBeCreatedByCopyAssignment) {
    WeakPtr<int> copyTestWeakPtr{};
    copyTestWeakPtr = testWeakPtr;

    ASSERT_FALSE(copyTestWeakPtr.expired());
    ASSERT_FALSE(testWeakPtr.expired());
}

TEST_F(WeakPtrTest, ShouldPtrBeCreatedByMoveCtor) {
    WeakPtr<int> moveTestWeakPtr{std::move(testWeakPtr)};

    ASSERT_FALSE(moveTestWeakPtr.expired());
    ASSERT_TRUE(testWeakPtr.expired());
}

TEST_F(WeakPtrTest, ShouldPtrBeCreatedByMoveAssignment) {
    WeakPtr<int> moveTestWeakPtr{};
    moveTestWeakPtr = std::move(testWeakPtr);

    ASSERT_FALSE(moveTestWeakPtr.expired());
    ASSERT_TRUE(testWeakPtr.expired());
}

TEST_F(WeakPtrTest, ShouldLockTestWeakPtr) {
    SharedPtr<int> lockSharedPtr{testWeakPtr.lock()};

    ASSERT_EQ(*lockSharedPtr, initValue);
    ASSERT_FALSE(testWeakPtr.expired());
}

TEST_F(WeakPtrTest, ShouldEmptyTestWeakPtrLockReturnEmptySharedPtr) {
    WeakPtr<int> emptyWeakPtr{};
    SharedPtr<int> lockSharedPtr{emptyWeakPtr.lock()};

    ASSERT_EQ(lockSharedPtr.get(), nullptr);
    ASSERT_FALSE(testWeakPtr.expired());
}
