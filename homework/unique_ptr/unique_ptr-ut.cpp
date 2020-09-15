#include <gtest/gtest.h>

#include "PtrIsNullptr.hpp"
#include "unique_ptr.hpp"

constexpr int initValue = 5;
constexpr int newValue = 6;

struct A {
    int foo() { return initValue; }
};

struct unique_ptrTest : ::testing::Test {
    unique_ptrTest()
        : ptr(new int{initValue}) {}
    unique_ptr<int> ptr;
};

TEST_F(unique_ptrTest, shouldBeAbleToDereferencePtr) {
    ASSERT_EQ(*ptr, initValue);

    *ptr = newValue;
    ASSERT_EQ(*ptr, newValue);
}

TEST_F(unique_ptrTest, shouldMovePtr) {
    unique_ptr<int> ptr2 = std::move(ptr);
    ASSERT_EQ(*ptr2, initValue);
    ASSERT_EQ(ptr.get(), nullptr);
}

TEST_F(unique_ptrTest, shouldUseResetMethod) {
    ptr.reset(new int{newValue});
    ASSERT_EQ(*ptr, newValue);
}

TEST_F(unique_ptrTest, shouldUseGetMethod) {
    auto p = ptr.get();
    ASSERT_EQ(*ptr, *p);
}

TEST_F(unique_ptrTest, shouldUseReleaseMethod) {
    auto p = ptr.release();
    ASSERT_EQ(*p, initValue);
    ASSERT_EQ(ptr.get(), nullptr);
    delete p;
}

TEST(unique_ptrTestArrow, shouldUseArrowOperator) {
    unique_ptr<A> ptr(new A{});
    ASSERT_EQ(ptr->foo(), initValue);
}

TEST(unique_ptrTestDereferenceNull, shouldThrowExceptionIfDereferenceNullptr) {
    unique_ptr<int> ptr;
    ASSERT_THROW(*ptr, PtrIsNullptr);
}
