#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "shared_ptr.hpp"

using ::testing::IsNull;

constexpr int initialValue = 5;

struct A {
    int foo() { return initialValue; }
};

struct SharedPtrTest : ::testing::Test {
    SharedPtrTest()
        : ptr(new int{initialValue}) {}

    my::shared_ptr<int> ptr;
};

TEST_F(SharedPtrTest, shouldDereferenceSharedPtr) {
    ASSERT_EQ(*ptr, initialValue);
}

TEST_F(SharedPtrTest, shouldCopySharedPtr) {
    constexpr size_t numOfPtrs = 3;
    auto ptr2(ptr);
    my::shared_ptr<int> ptr3(new int{initialValue});

    ASSERT_EQ(*ptr2, *ptr);
    ASSERT_EQ(*ptr3, initialValue);
    ASSERT_EQ(ptr3.use_count(), 1);

    ptr3 = ptr;
    ASSERT_EQ(ptr.use_count(), numOfPtrs);
    ASSERT_EQ(ptr2.use_count(), numOfPtrs);
    ASSERT_EQ(ptr3.use_count(), numOfPtrs);
}

TEST_F(SharedPtrTest, shouldMoveSharedPtr) {
    auto ptr2(std::move(ptr));

    EXPECT_THAT(ptr.get(), IsNull());
    ASSERT_EQ(*ptr2, initialValue);
    ASSERT_EQ(ptr2.use_count(), 1);

    constexpr int ptr3InitialValue = 6;
    my::shared_ptr<int> ptr3(new int{ptr3InitialValue});

    ptr3 = std::move(ptr2);
    EXPECT_THAT(ptr2.get(), IsNull());
    ASSERT_EQ(*ptr3, initialValue);
    ASSERT_EQ(ptr3.use_count(), 1);
}

TEST_F(SharedPtrTest, shouldConvertSharedPtrToBool) {
    my::shared_ptr<int> ptr2;

    ASSERT_TRUE(ptr);
    ASSERT_FALSE(ptr2);
}

TEST_F(SharedPtrTest, shouldResetSharedPtr) {
    ptr.reset();

    ASSERT_THAT(ptr.get(), IsNull());

    constexpr int valueAfterReset = 6;
    auto newPtr = new int{valueAfterReset};

    ptr.reset(newPtr);

    ASSERT_EQ(*ptr, valueAfterReset);
}

TEST(SharedPtrArrowOperatorTest, shouldUseArrowOperator) {
    my::shared_ptr<A> ptr(new A{});

    ASSERT_EQ(ptr->foo(), initialValue);
}
