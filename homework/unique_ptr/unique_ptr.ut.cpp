#include <gtest/gtest.h>

#include "unique_ptr.hpp"

constexpr int expected = 42;
constexpr int newExpected = 21;

struct unique_ptr_test : public ::testing::Test {
    unique_ptr<int> ptr = new int{expected};
};

TEST_F(unique_ptr_test, shouldDereference) {
    ASSERT_EQ(*ptr, expected);
}

TEST_F(unique_ptr_test, shouldChangeValue) {
    *ptr = newExpected;
    ASSERT_EQ(*ptr, newExpected);
}

TEST_F(unique_ptr_test, shouldCreateNullptr) {
    unique_ptr<int> null_ptr;
    ASSERT_EQ(null_ptr.get(), nullptr);
}

TEST_F(unique_ptr_test, shouldRelease) {
    auto ptr2 = ptr.release();
    ASSERT_EQ(*ptr2, expected);
    ASSERT_EQ(ptr.get(), nullptr);
    delete ptr2;
}

TEST_F(unique_ptr_test, shouldReset) {
    ptr.reset(new int(newExpected));
    ASSERT_EQ(*ptr, newExpected);
    ptr.reset();
    ASSERT_EQ(ptr.get(), nullptr);
}

TEST_F(unique_ptr_test, shouldCreateByMoveConstructor) {
    unique_ptr<int> ptr(unique_ptr<int>{new int {expected}});
    unique_ptr<int> ptr2(std::move(ptr));
    ASSERT_EQ(ptr.get(), nullptr);
    ASSERT_EQ(*ptr2, expected);
}

TEST_F(unique_ptr_test, shoudlMoveByOperator) {
    unique_ptr<int> ptr{new int {expected}};
    unique_ptr<int> ptr2{new int {-expected}};
    ptr2 = std::move(ptr);
    ASSERT_EQ(ptr.get(), nullptr);
    ASSERT_EQ(*ptr2, expected);
}

TEST_F(unique_ptr_test, shouldArrowOperatorWorks) {
    struct square {
        int getArea() { return expected; }
    };
    unique_ptr<square> ptr = new square();
    ASSERT_EQ(ptr->getArea(), expected);
}


