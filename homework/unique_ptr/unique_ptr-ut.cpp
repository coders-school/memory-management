#include <gtest/gtest.h>

#include "unique_ptr.hpp"

constexpr int testValueOne = 10;
constexpr int testValueTwo = 20;

struct uniquePtrTest : ::testing::Test {
    uniquePtrTest()
        : uPtr(new int{testValueOne}) {}
    unique_ptr<int> uPtr;
};

TEST_F(uniquePtrTest, checkConstructors) {
    ASSERT_EQ(*uPtr, 10);
    unique_ptr<int> uPtr2(new int{testValueTwo});
    unique_ptr<int> uPtr3(std::move(uPtr2));
    ASSERT_EQ(*uPtr3, 20);
}