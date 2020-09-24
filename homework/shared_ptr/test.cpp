#include <string>
#include "gtest/gtest.h"
#include "shared_ptr.hpp"

const std::string testString{"Ala ma kota"};
constexpr int testValueOne = 10;

struct sharedPtrTest : ::testing::Test {
    sharedPtrTest()
    : sPtr(new int{testValueOne}) {}
    cs::shared_ptr<int> sPtr;
};

TEST_F(sharedPtrTest, TestConstructor) {
    ASSERT_EQ(*sPtr, testValueOne);
    cs::shared_ptr<int> sPtr2(std::move(sPtr));
    //cs::shared_ptr<int> sPtr2(sPtr);
    //ASSERT_EQ(*sPtr, *sPtr2);
}