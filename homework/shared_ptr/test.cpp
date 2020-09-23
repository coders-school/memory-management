#include <string>
#include "gtest/gtest.h"
#include "shared_ptr.hpp"

const std::string testString{"Ala ma kota"};

TEST(TestTest, FailTest) {
    ASSERT_TRUE(false);
}