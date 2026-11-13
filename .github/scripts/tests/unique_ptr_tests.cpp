#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "unique_ptr.hpp"

using ::testing::IsNull;

constexpr int initialValue = 5;

struct A {
    int foo() { return initialValue; }
};

struct UniquePtrTest : ::testing::Test {
    UniquePtrTest()
        : ptr(new int{initialValue}) {}

    my::unique_ptr<int> ptr;
};

TEST_F(UniquePtrTest, shouldDereferenceUniquePtr) {
    ASSERT_EQ(*ptr, initialValue);
}

TEST_F(UniquePtrTest, shouldMoveUniquePtr) {
    auto ptr2{std::move(ptr)};

    EXPECT_THAT(ptr.get(), IsNull());
    ASSERT_EQ(*ptr2, initialValue);

    my::unique_ptr<int> ptr3{};
    EXPECT_THAT(ptr3.get(), IsNull());

    ptr3 = std::move(ptr2);
    EXPECT_THAT(ptr2.get(), IsNull());
    ASSERT_EQ(*ptr3, initialValue);
}

TEST_F(UniquePtrTest, shouldUseResetMethod) {
    constexpr int newValue = 6;
    ptr.reset(new int{newValue});
    ASSERT_EQ(*ptr, newValue);

    ptr.reset();
    ASSERT_THAT(ptr.get(), IsNull());
}

TEST_F(UniquePtrTest, shouldUseGetMethod) {
    auto p = ptr.get();
    ASSERT_EQ(*ptr, *p);
}

TEST_F(UniquePtrTest, shouldUseReleaseMethod) {
    auto p = ptr.release();

    ASSERT_EQ(*p, initialValue);
    ASSERT_THAT(ptr.get(), IsNull());

    delete p;
}

TEST(UniquePtrTestArrow, shouldUseArrowOperator) {
    my::unique_ptr ptr(new A{});
    ASSERT_EQ(ptr->foo(), initialValue);
}
