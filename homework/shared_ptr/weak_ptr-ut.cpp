#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "weak_ptr.hpp"

constexpr int testValue = 10;
constexpr int secondTestValue = 666;

struct WeakPointerTest : ::testing::Test {
    WeakPointerTest()
        : sharedPtr(new int(testValue)) {}
    coders::shared_ptr<int> sharedPtr;
};

TEST_F(WeakPointerTest, ShouldCreateWeakPointerFromSharedUsingCopyConstructor) {
    // Given
    size_t ptrCount = 1;

    // When
    coders::weak_ptr<int> weakPtr(sharedPtr);

    // Then
    ASSERT_EQ(weakPtr.use_count(), ptrCount);
    ASSERT_EQ(*(weakPtr.lock()), *sharedPtr);
}

TEST_F(WeakPointerTest, ShouldCreateWeakPointerFromSharedUsingCopyAssignmentOperator) {
    // Given
    size_t ptrCount = 1;

    // When
    coders::weak_ptr<int> weakPtr;
    weakPtr = sharedPtr;

    // Then
    ASSERT_EQ(weakPtr.use_count(), ptrCount);
    ASSERT_EQ(*(weakPtr.lock()), *sharedPtr);
}

TEST_F(WeakPointerTest, ShouldCreateWeakPointerFromWeakUsingCopyConstructor) {
    // Given
    size_t ptrCount = 1;

    // When
    coders::weak_ptr<int> weakPtr(sharedPtr);
    coders::weak_ptr<int> anotherWeakPtr(weakPtr);

    // Then
    ASSERT_EQ(anotherWeakPtr.use_count(), ptrCount);
    ASSERT_EQ(*(anotherWeakPtr.lock()), *sharedPtr);
}

TEST_F(WeakPointerTest, ShouldCreateWeakPointerFromWeakUsingCopyAssignmentOperator) {
    // Given
    size_t ptrCount = 1;

    // When
    coders::weak_ptr<int> weakPtr(sharedPtr);
    coders::weak_ptr<int> anotherWeakPtr;
    anotherWeakPtr = weakPtr;

    // Then
    ASSERT_EQ(anotherWeakPtr.use_count(), ptrCount);
    ASSERT_EQ(*(anotherWeakPtr.lock()), *sharedPtr);
}

TEST_F(WeakPointerTest, ShouldCreateWeakPointerFromWeakUsingMoveConstructor) {
    // Given
    size_t ptrCount = 1;

    // When
    coders::weak_ptr<int> weakPtr(sharedPtr);
    coders::weak_ptr<int> anotherWeakPtr(std::move(weakPtr));

    // Then
    ASSERT_EQ(anotherWeakPtr.use_count(), ptrCount);
    ASSERT_EQ(*(anotherWeakPtr.lock()), *sharedPtr);
}

TEST_F(WeakPointerTest, ShouldCreateWeakPointerFromWeakUsingMoveAssignmentOperator) {
    // Given
    size_t ptrCount = 1;

    // When
    coders::weak_ptr<int> weakPtr(sharedPtr);
    coders::weak_ptr<int> anotherWeakPtr;
    anotherWeakPtr = std::move(weakPtr);

    // Then
    ASSERT_EQ(anotherWeakPtr.use_count(), ptrCount);
    ASSERT_EQ(*(anotherWeakPtr.lock()), *sharedPtr);
}

TEST_F(WeakPointerTest, ExpiredShouldReturnFalseWhenPointerIsValid) {
    // Given
    coders::weak_ptr<int> weakPtr(sharedPtr);

    // When
    // Then
    ASSERT_FALSE(weakPtr.expired());
}

TEST_F(WeakPointerTest, ExpiredShouldReturnTrueWhenPointerIsNotValid) {
    // Given
    coders::weak_ptr<int> weakPtr(sharedPtr);
    
    // When
    weakPtr.reset();

    // Then
    ASSERT_TRUE(weakPtr.expired());
}

TEST_F(WeakPointerTest, UseCountShouldReturnNonZeroValue) {
    // Given
    coders::weak_ptr<int> weakPtr(sharedPtr);

    // When
    // Then
    ASSERT_NE(weakPtr.use_count(), 0);
}

TEST_F(WeakPointerTest, UseCountShouldReturnZero) {
    // Given
    coders::weak_ptr<int> weakPtr{sharedPtr};

    // When
    weakPtr.reset();

    // Then
    ASSERT_EQ(weakPtr.use_count(), 0);
}

TEST_F(WeakPointerTest, ResetWeakPtrShouldDecreaseWeakRefs) {
    // Given
    coders::weak_ptr<int> weakPtr{sharedPtr};
    int weakRefs{0};
    int sharedRefs{1};

    // When
    weakPtr.reset();

    // Then
    ASSERT_EQ(weakPtr.use_count(), weakRefs);
    ASSERT_EQ(sharedPtr.use_count(), sharedRefs);
}

TEST_F(WeakPointerTest, WeakPointerShouldNotBeExpiredAfterReInitialization) {
    // Given
    coders::weak_ptr<int> weakPtr{sharedPtr};
    ASSERT_FALSE(weakPtr.expired());

    // When
    weakPtr.reset();
    ASSERT_TRUE(weakPtr.expired());
    weakPtr = sharedPtr;

    // Then
    ASSERT_FALSE(weakPtr.expired());
}
