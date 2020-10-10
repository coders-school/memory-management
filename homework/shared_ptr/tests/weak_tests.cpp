#include "weak.cpp"

#include <gtest/gtest.h>

class WeakTest : public ::testing::Test {
    public:
    int defaultValue{5};
    int anotherValue{10};
};

TEST_F(WeakTest, canBeDefaultCreated) {
    cs::weak_ptr<int> ptr{};
}

TEST_F(WeakTest, canBeCreatedFromSharedPtr) {
    cs::shared_ptr<int> shared{new int{defaultValue}};
    cs::weak_ptr<int> ptr{shared};
}
