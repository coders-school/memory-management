#include <gtest/gtest.h>

#include "make_shared.hpp"

struct A {
    A(int a, double b, int c)
        : a_(a), b_(b), c_(c) {}

    int a_;
    double b_;
    int c_;
};

struct B {
    B(int a, double b)
        : a_(a), b_(b) {}

    int a_;
    double b_;
};

TEST(MakeSharedTest, shouldCreateSharedPtrUsingMakeShared) {
    constexpr int firstValue = 1;
    constexpr double secondValue = 2;
    constexpr int thirdValue = 3;

    cs::shared_ptr<A> ptr = cs::make_shared<A>(firstValue, secondValue, thirdValue);

    ASSERT_EQ(ptr->a_, firstValue);
    ASSERT_EQ(ptr->b_, secondValue);
    ASSERT_EQ(ptr->c_, thirdValue);

    cs::shared_ptr<B> ptr2 = cs::make_shared<B>(firstValue, secondValue);

    ASSERT_EQ(ptr2->a_, firstValue);
    ASSERT_EQ(ptr2->b_, secondValue);
}
