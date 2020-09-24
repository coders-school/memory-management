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
    ASSERT_EQ(*sPtr2, testValueOne);
    //cs::shared_ptr<int> sPtr3(sPtr);
    //ASSERT_EQ(*sPtr2, *sPtr3);
}

TEST_F(sharedPtrTest, testGet) {
    auto ptr = sPtr.get();
    ASSERT_EQ(*ptr, *sPtr);
    ptr = sPtr.release();
    delete ptr;
}

TEST_F(sharedPtrTest, testOperator) {
    cs::shared_ptr<std::string> uPtr2(new std::string{testString});
    ASSERT_EQ(uPtr2->at(0), 'A');
    ASSERT_EQ(uPtr2->at(1), 'l');
}