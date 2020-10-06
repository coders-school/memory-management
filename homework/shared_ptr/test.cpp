#include <string>
#include "gtest/gtest.h"
#include "control_block.hpp"
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

const std::string testString{"Ala ma kota"};
constexpr int testValueOne = 10;
constexpr int testValueTwo = 20;

struct sharedPtrTest : ::testing::Test {
    sharedPtrTest()
    : sPtr(new int{testValueOne}) {}
    cs::shared_ptr<int> sPtr;
};

TEST_F(sharedPtrTest, testCounter) {
    ASSERT_EQ(sPtr.use_count(), 1);
    {
        cs::shared_ptr<int> testPtr(sPtr);
        ASSERT_EQ(sPtr.use_count(), 2);
    };
    ASSERT_EQ(sPtr.use_count(), 1);
}

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

TEST_F(sharedPtrTest, testSwap) {
    cs::shared_ptr<int> testPtr(new int(testValueTwo));
    cs::shared_ptr<int> counterIncreaser(sPtr);
    auto higherUseCount = sPtr.use_count();
    auto lowerUseCount = testPtr.use_count();
    testPtr.swap(sPtr);
    ASSERT_EQ(*sPtr, testValueTwo);
    ASSERT_EQ(*testPtr, testValueOne);
    ASSERT_EQ(testPtr.use_count(), higherUseCount);
    ASSERT_EQ(sPtr.use_count(), lowerUseCount);
}

TEST_F(sharedPtrTest, testAccessOperator) {
    cs::shared_ptr<std::string> uPtr2(new std::string{testString});
    ASSERT_EQ(uPtr2->at(0), 'A');
    ASSERT_EQ(uPtr2->at(1), 'l');
}

TEST(sharedPointerTest, shouldCreateWithoutArguments) {
    cs::shared_ptr<int> ptr;

    ASSERT_EQ(ptr.get(), nullptr);
}

// TEST(sharedPointerTest, shouldUseMakeShared) {
//     auto ptr = cs::make_shared(testValueOne);

//     ASSERT_EQ(*ptr, testValueOne);
// }

// TEST(sharedPointerTest, shouldUseMakeSharedOnSTLDataStructs) {
//     std::vector<int> testVector{1,2};

//     auto ptr = cs::make_shared<std::vector<int>>({1,2});

//     ASSERT_EQ(*ptr, testVector);
// }

TEST(sharedPointerTest, shouldUseVariadicMakeShared) {
    std::vector<int> testVector{1,2};

    auto ptr = cs::make_shared<std::vector<int>>(1,2);

    ASSERT_EQ(*ptr, testVector);
}

struct weakPtrTest : ::testing::Test {
    weakPtrTest()
        : sPtr(new int{testValueOne}) {}
    cs::shared_ptr<int> sPtr;
};

TEST_F(weakPtrTest, shouldConstruct) {
    cs::weak_ptr<int> weak(sPtr);

    ASSERT_EQ(*(weak.lock()), *sPtr);
}

TEST_F(weakPtrTest, shouldCopyAssign) {
    cs::weak_ptr<int> weakOne(sPtr);
    cs::weak_ptr<int> weakTwo;
    weakTwo = weakOne;

    ASSERT_EQ(*(weakOne.lock()), *(weakTwo.lock()));
}

TEST_F(weakPtrTest, testLock) {
    cs::weak_ptr<int> weak(sPtr);

    ASSERT_EQ(*(weak.lock()), testValueOne);
}