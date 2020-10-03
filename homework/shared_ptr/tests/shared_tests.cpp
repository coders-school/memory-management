#include <gtest/gtest.h>
#include "shared.cpp"

class SharedTest :public ::testing::Test {
    protected:


};

TEST_F(SharedTest, canBeCreated) {
    cs::shared_ptr<int> test;
}
