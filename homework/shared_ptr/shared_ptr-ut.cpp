#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "shared_ptr.hpp"

constexpr int testValue = 10;
constexpr int secondTestValue = 666;

struct SharedPointerTest : ::testing::Test {
    SharedPointerTest()
        : sharedPtr(new int(testValue)) {}
    coders::shared_ptr<int> sharedPtr;
};

TEST_F(SharedPointerTest, ShouldCreateNullptrSharedPointerToIntegerUsingDefaultConstructor) {
    // Given
    size_t sharedPtrCnt = 1;

    // When
    coders::shared_ptr<int> emptySharedPtr{};

    // Then
    ASSERT_FALSE(emptySharedPtr);
    ASSERT_EQ(emptySharedPtr.get(), nullptr);
    ASSERT_EQ(emptySharedPtr.operator->(), nullptr);
    ASSERT_EQ(emptySharedPtr.use_count(), sharedPtrCnt);
}

TEST_F(SharedPointerTest, ShouldCreateSharedPointerToIntegerUsingBasicConstructor) {
    // Given
    size_t sharedPtrCnt = 1;

    // When
    // Then
    ASSERT_TRUE(sharedPtr);
    ASSERT_EQ(sharedPtr.use_count(), sharedPtrCnt);
    ASSERT_EQ(*sharedPtr.get(), testValue);
}

TEST_F(SharedPointerTest, ShouldCreateSharedPointerUsingCopyConstructor) {
    // Given
    size_t sharedPtrCnt = 1;
    ASSERT_EQ(sharedPtr.use_count(), sharedPtrCnt);
    ASSERT_EQ(*sharedPtr.get(), testValue);

    // When
    auto newShared(sharedPtr);
    ++sharedPtrCnt;

    // Then
    ASSERT_TRUE(newShared);
    ASSERT_EQ(newShared.use_count(), sharedPtrCnt);
    ASSERT_EQ(*newShared.get(), testValue);
}

TEST_F(SharedPointerTest, ShouldCreateSharedPointerUsingCopyAssignmentOperator) {
    // Given
    size_t sharedPtrCnt = 1;
    ASSERT_EQ(sharedPtr.use_count(), sharedPtrCnt);
    ASSERT_EQ(*sharedPtr.get(), testValue);

    // When
    coders::shared_ptr<int> newShared;
    newShared = sharedPtr;
    ++sharedPtrCnt;

    // Then
    ASSERT_TRUE(newShared);
    ASSERT_EQ(newShared.use_count(), sharedPtrCnt);
    ASSERT_EQ(*newShared.get(), testValue);
}

TEST_F(SharedPointerTest, ShouldCreateSharedPointerUsingMoveConstructor) {
    // Given
    size_t sharedPtrCnt = 1;
    ASSERT_EQ(sharedPtr.use_count(), sharedPtrCnt);
    ASSERT_EQ(*sharedPtr.get(), testValue);

    // When
    coders::shared_ptr<int> newShared(std::move(sharedPtr));

    // Then
    ASSERT_FALSE(sharedPtr);
    ASSERT_TRUE(newShared);
    ASSERT_EQ(newShared.use_count(), sharedPtrCnt);
    ASSERT_EQ(*newShared.get(), testValue);
}

TEST_F(SharedPointerTest, ShouldCreateSharedPointerUsingMoveAssignmentOperator) {
    // Given
    size_t sharedPtrCnt = 1;
    ASSERT_EQ(sharedPtr.use_count(), sharedPtrCnt);
    ASSERT_EQ(*sharedPtr.get(), testValue);

    // When
    coders::shared_ptr<int> newShared;
    newShared = std::move(sharedPtr);

    // Then
    ASSERT_FALSE(sharedPtr);
    ASSERT_TRUE(newShared);
    ASSERT_EQ(newShared.use_count(), sharedPtrCnt);
    ASSERT_EQ(*newShared.get(), testValue);
}

TEST_F(SharedPointerTest, ShouldResetSharedPointerToGivenValue) {
    // Given
    size_t sharedPtrCnt = 1;
    int newValue = 666;
    ASSERT_EQ(sharedPtr.use_count(), sharedPtrCnt);
    ASSERT_EQ(*sharedPtr.get(), testValue);

    // When
    sharedPtr.reset(new int(newValue));

    // Then
    ASSERT_TRUE(sharedPtr);
    ASSERT_EQ(sharedPtr.use_count(), sharedPtrCnt);
    ASSERT_EQ(*sharedPtr.get(), newValue);
}

TEST_F(SharedPointerTest, ShouldResetSharedPointerToNullptr) {
    // Given
    size_t sharedPtrCnt = 1;
    ASSERT_EQ(sharedPtr.use_count(), sharedPtrCnt);
    ASSERT_EQ(*sharedPtr.get(), testValue);

    // When
    sharedPtr.reset();

    // Then
    ASSERT_FALSE(sharedPtr);
    ASSERT_EQ(sharedPtr.get(), nullptr);
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