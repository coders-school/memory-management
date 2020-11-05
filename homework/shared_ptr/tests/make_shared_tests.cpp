#include "shared.hpp"

#include <gtest/gtest.h>

struct Custom {
    int first_{5};
    double second_{3.0};
    bool third_{false};
    Custom() = default;
    Custom(int first, double second, bool third) : first_(first), second_(second), third_(third) {}
};
class makeSharedTests : public ::testing::Test
{
   public:
    int defaultValue{5};
    Custom myCustom{2, 5.0, true};
    cs::shared_ptr<int> defaultShared{new int{defaultValue}};
};

TEST_F(makeSharedTests, sharedPtrCanBeCreatedByMakeShared)
{
    auto shared = cs::make_shared<int>(defaultValue);
    EXPECT_EQ(*shared, defaultValue);
};

TEST_F(makeSharedTests, makeSharedCreatesSharedWithDefaultCustomObject)
{
    auto expectedFirstValue = 5;
    auto expectedSecondValue = 3.0;
    auto expectedThirdValue = false;
    auto shared = cs::make_shared<Custom>();
    EXPECT_EQ(shared->first_, expectedFirstValue);
    EXPECT_EQ(shared->second_, expectedSecondValue);
    EXPECT_EQ(shared->third_, expectedThirdValue);
};

TEST_F(makeSharedTests, makeSharedCreatesSharedWithNonDefaultCustomObject) {
    auto shared = cs::make_shared<Custom>(myCustom);
    auto expectedFirstValue{2};
    auto expectedSecondValue{5.0};
    auto expectedThirdValue{true};
    EXPECT_EQ(shared->first_, expectedFirstValue);
    EXPECT_EQ(shared->second_, expectedSecondValue);
    EXPECT_EQ(shared->third_, expectedThirdValue);
};

TEST_F(makeSharedTests, makeSharedCreatesSharedWithManyArgumentsInCustomObject) {
    auto expectedFirstValue{2};
    auto expectedSecondValue{5.0};
    auto expectedThirdValue{true};
    auto shared = cs::make_shared<Custom>(expectedFirstValue, expectedSecondValue, expectedThirdValue);
    EXPECT_EQ(shared->first_, expectedFirstValue);
    EXPECT_EQ(shared->second_, expectedSecondValue);
    EXPECT_EQ(shared->third_, expectedThirdValue);
};
