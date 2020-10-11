#include <gtest/gtest.h>
#include "shared.hpp"

class makeSharedTests :public ::testing::Test {
    public:
    int defaultValue{5};
    cs::shared_ptr<int> defaultShared{new int{defaultValue}};
};

TEST_F(makeSharedTests, sharedPtrCanBeCreatedByMakeShared) {
    auto shared = cs::make_shared<int>(defaultValue);
    EXPECT_EQ(*shared, defaultValue);
}
