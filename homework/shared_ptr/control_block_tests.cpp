#include <gtest/gtest.h>
#include "shared_ptr.hpp"

class controlBlockFixture : public ::testing::Test {
public:
    ~controlBlockFixture() {
    }

protected:
};

TEST_F(controlBlockFixture, SampleTest) {
    EXPECT_TRUE(true);
}