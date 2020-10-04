#include <gtest/gtest.h>

#include "SharedControlBlock.hpp"
#include "SharedPtr.hpp"

constexpr size_t initSharedValue = 1;
constexpr size_t initWeakValue = 0;

struct SharedControlBlockTest : public ::testing::Test {
    SharedControlBlock<int> testSharedControlBlock;
};

TEST_F(SharedControlBlockTest, ShouldGetSharedRefsCount) {
    ASSERT_EQ(testSharedControlBlock.getSharedRefsCount(), initSharedValue);
}

TEST_F(SharedControlBlockTest, ShouldIncrementSharedRefsCount) {
    testSharedControlBlock.incrementSharedRefsCount();
    ASSERT_EQ(testSharedControlBlock.getSharedRefsCount(), initSharedValue + 1);
}

TEST_F(SharedControlBlockTest, ShouldDecrementSharedRefsCount) {
    testSharedControlBlock.decrementSharedRefsCount();
    ASSERT_EQ(testSharedControlBlock.getSharedRefsCount(), initSharedValue - 1);
}

TEST_F(SharedControlBlockTest, ShouldGetWeakRefsCount) {
    ASSERT_EQ(testSharedControlBlock.getWeakRefsCount(), initWeakValue);
}

TEST_F(SharedControlBlockTest, ShouldIncrementWeakRefsCount) {
    testSharedControlBlock.incrementWeakRefsCount();
    ASSERT_EQ(testSharedControlBlock.getWeakRefsCount(), initWeakValue + 1);
}

TEST_F(SharedControlBlockTest, ShouldDecrementWeakRefsCount) {
    testSharedControlBlock.incrementWeakRefsCount();
    testSharedControlBlock.decrementWeakRefsCount();
    ASSERT_EQ(testSharedControlBlock.getWeakRefsCount(), initWeakValue);
}
