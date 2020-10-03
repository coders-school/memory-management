#include <gtest/gtest.h>
#include "shared.cpp"

class SharedTest :public ::testing::Test {
    protected:
    int defaultValue{5};

};

TEST_F(SharedTest, defaultSharedShouldBeNullptr) {
    cs::shared_ptr<int> test;
    EXPECT_EQ(test.get(), nullptr);
}

TEST_F(SharedTest, sharedWhenCreatedFromRawPtrShouldAllocateControlBlock) {
    cs::shared_ptr<int> test(new int{defaultValue});
    EXPECT_EQ(test.use_count(), 1);
}

TEST_F(SharedTest, sharedWhenCopiedShouldIncreaseRefCount) {
    cs::shared_ptr<int> test(new int{defaultValue});
    cs::shared_ptr<int> test2(test);
    EXPECT_EQ(test.use_count(), 2);
    EXPECT_EQ(test2.use_count(), 2);
}
