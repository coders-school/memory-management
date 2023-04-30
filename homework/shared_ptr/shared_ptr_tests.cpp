
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
