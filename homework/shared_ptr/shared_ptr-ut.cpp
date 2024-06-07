#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

constexpr int testValue = 10;
constexpr int anotherTestValue = 666;

struct SharedPointerTest : ::testing::Test {
    coders::shared_ptr<int> sharedPtr{new int(testValue)};
};

TEST_F(SharedPointerTest, ShouldCreateNullptrSharedPointerToIntegerUsingDefaultConstructor) {
    // Given
    size_t expectedSharedCount = 0;

    // When
    coders::shared_ptr<int> emptySharedPtr{};

    // Then
    ASSERT_FALSE(emptySharedPtr);
    ASSERT_EQ(emptySharedPtr.get(), nullptr);
    ASSERT_EQ(emptySharedPtr.operator->(), nullptr);
    ASSERT_EQ(emptySharedPtr.use_count(), expectedSharedCount);
}

TEST_F(SharedPointerTest, ShouldCreateSharedPointerToIntegerUsingBasicConstructor) {
    // Given
    size_t expectedSharedCount = 1;

    // When
    // Then
    ASSERT_TRUE(sharedPtr);
    ASSERT_EQ(sharedPtr.use_count(), expectedSharedCount);
    ASSERT_EQ(*sharedPtr.get(), testValue);
}

TEST_F(SharedPointerTest, ShouldCreateSharedPointerUsingCopyConstructor) {
    // Given
    size_t expectedSharedCount = 1;
    ASSERT_EQ(sharedPtr.use_count(), expectedSharedCount);
    ASSERT_EQ(*sharedPtr.get(), testValue);

    // When
    auto newShared(sharedPtr);

    // Then
    ASSERT_TRUE(newShared);
    ASSERT_EQ(newShared.use_count(), expectedSharedCount + 1);
    ASSERT_EQ(*newShared.get(), testValue);
}

TEST_F(SharedPointerTest, ShouldCreateSharedPointerUsingCopyAssignmentOperator) {
    // Given
    size_t expectedSharedCount = 1;
    ASSERT_EQ(sharedPtr.use_count(), expectedSharedCount);
    ASSERT_EQ(*sharedPtr.get(), testValue);

    // When
    coders::shared_ptr<int> newShared{new int{0}};
    newShared = sharedPtr;
    ++expectedSharedCount;

    // Then
    ASSERT_TRUE(newShared);
    ASSERT_EQ(newShared.use_count(), expectedSharedCount);
    ASSERT_EQ(*newShared.get(), testValue);
}

TEST_F(SharedPointerTest, ShouldCreateSharedPointerUsingMoveConstructor) {
    // Given
    size_t expectedSharedCount = 1;
    ASSERT_EQ(sharedPtr.use_count(), expectedSharedCount);
    ASSERT_EQ(*sharedPtr.get(), testValue);

    // When
    coders::shared_ptr<int> newShared(std::move(sharedPtr));

    // Then
    ASSERT_FALSE(sharedPtr);
    ASSERT_TRUE(newShared);
    ASSERT_EQ(newShared.use_count(), expectedSharedCount);
    ASSERT_EQ(*newShared.get(), testValue);
}

TEST_F(SharedPointerTest, ShouldCreateSharedPointerUsingMoveAssignmentOperator) {
    // Given
    size_t expectedSharedCount = 1;
    ASSERT_EQ(sharedPtr.use_count(), expectedSharedCount);
    ASSERT_EQ(*sharedPtr.get(), testValue);

    // When
    coders::shared_ptr<int> newShared{new int{0}};
    newShared = std::move(sharedPtr);

    // Then
    ASSERT_FALSE(sharedPtr);
    ASSERT_TRUE(newShared);
    ASSERT_EQ(newShared.use_count(), expectedSharedCount);
    ASSERT_EQ(*newShared.get(), testValue);
}

TEST_F(SharedPointerTest, ShouldResetSharedPointerToGivenValue) {
    // Given
    size_t expectedSharedCount = 1;
    int newValue = 666;
    ASSERT_EQ(sharedPtr.use_count(), expectedSharedCount);
    ASSERT_EQ(*sharedPtr.get(), testValue);

    // When
    sharedPtr.reset(new int(newValue));

    // Then
    ASSERT_TRUE(sharedPtr);
    ASSERT_EQ(sharedPtr.use_count(), expectedSharedCount);
    ASSERT_EQ(*sharedPtr.get(), newValue);
}

TEST_F(SharedPointerTest, ShouldResetSharedPointerToNullptr) {
    // Given
    size_t expectedSharedCount = 1;
    ASSERT_EQ(sharedPtr.use_count(), expectedSharedCount);
    ASSERT_EQ(*sharedPtr.get(), testValue);

    // When
    sharedPtr.reset();

    // Then
    ASSERT_FALSE(sharedPtr);
    ASSERT_EQ(sharedPtr.get(), nullptr);
    ASSERT_EQ(sharedPtr.use_count(), 0);
}

TEST_F(SharedPointerTest, ShouldUseOperators) {
    // Given
    std::vector<int> testVector{7, 3, 5};
    coders::shared_ptr<std::vector<int>> sharedPtr(new std::vector<int>(testVector));

    // When
    // Then
    ASSERT_EQ(*(sharedPtr->begin()), 7);
    ASSERT_EQ(*sharedPtr, testVector);
}

TEST(SharedPointerTestWithDeleter, ShouldUseGivenDeleter) {
    // Given
    struct testStruct {
        int a = 20;
    };
    testStruct* tStruct = new testStruct();
    auto testDeleter = [](testStruct* p) {
        std::cout << "My deleter!\n";
        p->a = -1;
    };

    // When
    {
        coders::shared_ptr<testStruct> testPtr(tStruct, testDeleter);
    }

    // Then
    ASSERT_EQ(tStruct->a, -1);
    delete tStruct;
}

TEST(SharedPointerTestWithWeaks, ShouldThrowWhenConstructedFromEmptyWeakPtr) {
    // Given
    coders::weak_ptr<int> wPtr{};

    // When
    // Then
    EXPECT_THROW(coders::shared_ptr<int> sharedPtr{wPtr}, coders::ExpiredWeakPtr);
}

TEST(SharedPointerTestWithWeaks, ShouldThrowWhenConstructedFromDanglingWeakPtr) {
    // Given
    coders::shared_ptr<int> sharedPtr(new int(testValue));
    coders::weak_ptr<int> wPtr{sharedPtr};

    // When
    wPtr.reset();

    // Then
    EXPECT_THROW(coders::shared_ptr<int> sPtr{wPtr}, coders::ExpiredWeakPtr);
}