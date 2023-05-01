
#include <gtest/gtest.h>
#include "shared_ptr.hpp"

#include <iostream>
#include <string>

template <class T>
class shared_ptr;

template class my::shared_ptr<int>;  // for coverage?

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

class SharedPtrClassTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    SharedPtrClassTest() {
        // You can do set-up work for each test here.
    }

    ~SharedPtrClassTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
    // for Foo.
};

TEST_F(SharedPtrClassTest, whenCreated_thenPossibleToDelete) {
    my::shared_ptr<int> shared_ptr{nullptr};
}

TEST_F(SharedPtrClassTest, whenCreatedPtrToInt_thenPossibleToDelete) {
    my::shared_ptr<int> shared_ptr{new int(7)};
}
