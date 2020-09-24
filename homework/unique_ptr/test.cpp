#include "md_unique_ptr.hpp"
#include "gtest/gtest.h"

class Test : public testing::Test {
public:
  void SetUp() override {
  }
};

TEST_F(Test, xxxx) {
    int expected = 1;
    int result = 1;
        EXPECT_EQ(expected, result);
}

