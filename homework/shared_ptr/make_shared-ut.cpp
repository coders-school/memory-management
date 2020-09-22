#include <gtest/gtest.h>

#include "make_shared.hpp"

struct A {
    A(int a, int b, int c)
        : a_(a), b_(b), c_(c) {}

    int a_;
    int b_;
    int c_;
};

TEST(MakeSharedTest, shouldCreateSharedPtrUsingMakeShared) {
    constexpr int firstValue = 1;
    constexpr int secondValue = 2;
    constexpr int thirdValue = 3;

    cs::shared_ptr<A> ptr = cs::make_shared<A>(firstValue, secondValue, thirdValue);

    ASSERT_EQ(ptr->a_, firstValue);
    ASSERT_EQ(ptr->b_, secondValue);
    ASSERT_EQ(ptr->c_, thirdValue);
}
