#include <gtest/gtest.h>

#include <type_traits>

#include "make_shared.hpp"

struct A {
    A(int a, double b, int c)
        : a_(a), b_(b), c_(c) {}

    int a_;
    double b_;
    int c_;
};

TEST(MakeSharedTest, shouldCreateSharedPtrUsingMakeShared) {
    constexpr int firstValue = 1;
    constexpr double secondValue = 2.3;
    constexpr int thirdValue = 3;

    constexpr int numOfPtrsAfterCopy = 2;
    constexpr int numOfPtrsAfterDelete = 1;

    auto ptr = my::make_shared<A>(firstValue, secondValue, thirdValue);
    bool isSharedPtrTypeRight = std::is_same_v<my::shared_ptr<A>, decltype(ptr)>;
    ASSERT_TRUE(isSharedPtrTypeRight);

    ASSERT_EQ(ptr->a_, firstValue);
    ASSERT_EQ(ptr->b_, secondValue);
    ASSERT_EQ(ptr->c_, thirdValue);

    auto ptr_copy = ptr;
    ASSERT_EQ(ptr.use_count(), numOfPtrsAfterCopy);
    ptr_copy.reset();
    ASSERT_EQ(ptr.use_count(), numOfPtrsAfterDelete);
}
