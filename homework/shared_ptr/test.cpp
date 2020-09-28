#include <string>
#include "gtest/gtest.h"
#include "control_block.hpp"
#include "shared_ptr.hpp"

const std::string testString{"Ala ma kota"};
constexpr int testValueOne = 10;
constexpr int testValueTwo = 20;

struct sharedPtrTest : ::testing::Test {
    sharedPtrTest()
    : sPtr(new int{testValueOne}) {}
    cs::shared_ptr<int> sPtr;
};

TEST_F(sharedPtrTest, testCopyConstructor) {
    ASSERT_EQ(*sPtr, testValueOne);
    ASSERT_EQ(sPtr.use_count(), 1);
    auto sPtr2(sPtr);
    auto sPtr3 = sPtr;
    ASSERT_EQ(*sPtr, *sPtr2);
    ASSERT_EQ(*sPtr, *sPtr3);
    ASSERT_EQ(sPtr3.use_count(), 3);
}

TEST_F(sharedPtrTest, testMoveConstructor) {
    auto sPtr2(std::move(sPtr));
    ASSERT_EQ(*sPtr2, testValueOne);
    auto sPtr3 = std::move(sPtr2);
    ASSERT_EQ(*sPtr3, testValueOne);
    ASSERT_EQ(sPtr3.use_count(), 1);
}

TEST_F(sharedPtrTest, testGet) {
    auto ptr = sPtr.get();
    auto ptr2 = sPtr.get();
    ASSERT_EQ(*ptr, *ptr2);
}

TEST_F(sharedPtrTest, testReset) {
    sPtr.reset(new int{testValueTwo});
    ASSERT_EQ(*sPtr, testValueTwo);
}

TEST(PointerTest, shouldCreateWithoutArguments) {
    cs::shared_ptr<int> ptr;

    ASSERT_ANY_THROW(*ptr);
}

// TEST_F(sharedPtrTest, testSwap) {
//     auto sPtr2 (new int{testValueTwo});
//     sPtr.swap(sPtr2);
//     ASSERT_EQ(*sPtr, testValueTwo);
//     ASSERT_EQ(*sPtr2, testValueOne);
// }

TEST_F(sharedPtrTest, testOperator) {
    cs::shared_ptr<std::string> uPtr2(new std::string{testString});
    ASSERT_EQ(uPtr2->at(0), 'A');
    ASSERT_EQ(uPtr2->at(1), 'l');
} 