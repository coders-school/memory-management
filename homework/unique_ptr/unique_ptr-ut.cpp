#include <gtest/gtest.h>
#include <string>
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

TEST_F(uniquePtrTest, checkOperators) {
    unique_ptr<std::string> uPtr2(new std::string{"AbCd"});
    ASSERT_EQ(uPtr2->at(0), 'A');
    ASSERT_EQ(uPtr2->at(1), 'b');
    ASSERT_EQ(uPtr2->at(2), 'C');
    ASSERT_EQ(uPtr2->at(3), 'd');
}

TEST_F(uniquePtrTest, checkGet) {
    auto ptr = uPtr.get();
    ASSERT_EQ(*ptr, *uPtr);
}

TEST_F(uniquePtrTest, checkRelease) {
    auto ptr = uPtr.release();
    ASSERT_EQ(*ptr, testValueOne);
    ASSERT_EQ(uPtr.get(), nullptr);
}