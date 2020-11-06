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
    constexpr double secondValue = 2.3;
    constexpr int thirdValue = 3;

    constexpr int numOfPtrsAfterCopy = 2;
    constexpr int numOfPtrsAfterDelete = 1;

    cs::shared_ptr<A> ptr = cs::make_shared<A>(firstValue, secondValue, thirdValue);

    ASSERT_EQ(ptr->a_, firstValue);
    ASSERT_EQ(ptr->b_, secondValue);
    ASSERT_EQ(ptr->c_, thirdValue);

    auto ptr_copy = ptr;
    ASSERT_EQ(ptr.use_count(), numOfPtrsAfterCopy);
    ptr_copy.reset();
    ASSERT_EQ(ptr.use_count(), numOfPtrsAfterDelete);

    cs::shared_ptr<B> ptr2 = cs::make_shared<B>(firstValue, secondValue);

    ASSERT_EQ(ptr2->a_, firstValue);
    ASSERT_EQ(ptr2->b_, secondValue);

    auto ptr2_copy = ptr;
    ASSERT_EQ(ptr.use_count(), numOfPtrsAfterCopy);
    ptr2_copy.reset();
    ASSERT_EQ(ptr.use_count(), numOfPtrsAfterDelete);
}
