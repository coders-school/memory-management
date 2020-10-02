#include "unique_ptr.hpp"
#include "gtest/gtest.h"

constexpr int testingValue = 10;
constexpr int testingValueSecond = 20;

struct UniquePtrTest : public testing::Test{
    unique_ptr<int> uniquePtr{new int(testingValue)};
};

TEST_F(UniquePtrTest, ConstructorShouldAssingTestingValue){
    ASSERT_EQ(*uniquePtr, testingValue);
}

TEST_F(UniquePtrTest, ResetFunctionShouldAssingNullptrToPtr){
    uniquePtr.reset(nullptr);

    ASSERT_EQ(uniquePtr.get(), nullptr);
}

TEST_F(UniquePtrTest, ShouldThrowExceptionWhenTryingToDereferenceNullptr){
    uniquePtr.reset(nullptr);

    EXPECT_THROW(*uniquePtr, std::exception);
}

TEST_F(UniquePtrTest, ShouldMoveFromAnotherUniquePtrUsingMoveOperator){
    unique_ptr<int> uniquePtr2{new int(testingValueSecond)};
    uniquePtr = std::move(uniquePtr2);

    ASSERT_EQ(*uniquePtr, testingValueSecond);
    ASSERT_EQ(uniquePtr2.get(), nullptr);
}

TEST_F(UniquePtrTest, ShouldMoveFromAnotherUniquePtrUsingConstructor){
    unique_ptr<int> uniquePtr2{new int(testingValue)};
    unique_ptr<int> uniquePtr3{std::move(uniquePtr2)};

    ASSERT_EQ(*uniquePtr3, testingValue);
    ASSERT_EQ(uniquePtr2.get(), nullptr);
}

TEST_F(UniquePtrTest, ResetFunctionShouldAssing10ToPtr){
    uniquePtr.reset(new int(testingValue));

    ASSERT_EQ(*uniquePtr, testingValue);
}

TEST_F(UniquePtrTest, ReleaseMethodShouldReleaseOwnership){
    auto testPtr = uniquePtr.release();

    ASSERT_EQ(*testPtr, testingValue);
    ASSERT_EQ(uniquePtr.get(), nullptr);

    delete testPtr;
}
