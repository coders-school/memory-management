#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "unique_ptr.hpp"

TEST(UniquePointerTest, ShouldCreateUniquePointerToIntegerUsingDefaultConstructor)
{
    // Given
    // When
    coders::unique_ptr<int> uniquePtr{};

    // Then
    ASSERT_EQ(uniquePtr.get(), nullptr);
}

TEST(UniquePointerTest, ShouldCreateUniquePointerToIntegerUsingBasicConstructor)
{
    // Given
    int testValue = 10;

    // When
    coders::unique_ptr<int> uniquePtr(new int(testValue));

    // Then
    ASSERT_EQ(*uniquePtr, testValue);
}

TEST(UniquePointerTest, ShouldGetRawPointerFromUniquePointerToInteger)
{
    // Given
    int testValue = 10;
    coders::unique_ptr<int> uniquePtr(new int(testValue));

    // When
    // Then
    ASSERT_EQ(*uniquePtr.get(), testValue);
}

TEST(UniquePointerTest, ShouldReleaseUniquePointerToString)
{
    // Given
    coders::unique_ptr<std::string> uniquePtr(new std::string("Hello world!"));

    // When
    auto rawPtrBeforeRelease = uniquePtr.get();
    auto releasedRawPtr = uniquePtr.release();

    // Then
    ASSERT_EQ(rawPtrBeforeRelease, releasedRawPtr);
    ASSERT_EQ(uniquePtr.get(), nullptr);

    delete releasedRawPtr;
}

TEST(UniquePointerTest, ShouldResetUniquePointerToVectorOfInts)
{
    // Given
    coders::unique_ptr<std::vector<int>> uniquePtr(new std::vector<int>{1, 2, 3});

    // When
    uniquePtr.reset(new std::vector<int>{10, 11});

    // Then
    ASSERT_EQ(uniquePtr->at(0), 10);
    ASSERT_EQ(uniquePtr->at(1), 11);
}

TEST(UniquePointerTest, ShouldResetUniquePointerWithoutArgument)
{
    // Given
    coders::unique_ptr<std::vector<int>> uniquePtr(new std::vector<int>{1, 2, 3});

    // When
    uniquePtr.reset();

    // Then
    ASSERT_EQ(uniquePtr.get(), nullptr);
}

TEST(UniquePointerTest, ShouldCreateUniquePointerToIntegerUsingMoveConstructor)
{
    // Given
    int testValue = 10;
    coders::unique_ptr<int> ptr1(new int(testValue));

    // When
    coders::unique_ptr<int> ptr2(std::move(ptr1));

    // Then
    ASSERT_EQ(ptr1.get(), nullptr);
    ASSERT_EQ(*ptr2, testValue);
}

TEST(UniquePointerTest, ShouldUseMoveAssignmentOnUniquePointerToDouble)
{
    // Given
    double testValue = 66.6;
    coders::unique_ptr<double> ptr1(new double(testValue));
    coders::unique_ptr<double> ptr2(new double(123.45));

    // When
    ptr2 = std::move(ptr1);

    // Then
    ASSERT_EQ(ptr1.get(), nullptr);
    ASSERT_EQ(*ptr2, testValue);
}
