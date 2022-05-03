#include <gtest/gtest.h>

#include "shared_ptr.hpp"

constexpr int initialValue = 5;

template class my::shared_ptr<int>;

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

    ASSERT_EQ(*ptr, *ptr2);
    ASSERT_EQ(*ptr, *ptr3);

    ASSERT_EQ(ptr3.use_count(), 1);
    ptr3 = ptr;
    ASSERT_EQ(ptr.use_count(), numOfPtrs);
    ASSERT_EQ(ptr2.use_count(), numOfPtrs);
    ASSERT_EQ(ptr3.use_count(), numOfPtrs);
}

TEST_F(SharedPtrTest, shouldMoveSharedPtr) {
    auto ptr2(std::move(ptr));
    ASSERT_EQ(*ptr2, initialValue);
    ASSERT_EQ(ptr2.use_count(), 1);

    my::shared_ptr<int> ptr3(new int{initialValue});
    ASSERT_EQ(ptr3.use_count(), 1);
    ptr3 = std::move(ptr2);
    ASSERT_EQ(*ptr3, initialValue);
    ASSERT_EQ(ptr3.use_count(), 1);
}

// TEST_F(SharedPtrTest, shouldConvertSharedPtrToBool) {
//     my::shared_ptr<int> ptr2;

//     ASSERT_TRUE(ptr);
//     ASSERT_FALSE(ptr2);
// }

// TEST_F(SharedPtrTest, shouldResetSharedPtr) {
//     ptr.reset();

//     ASSERT_EQ(ptr.get(), nullptr);

//     constexpr int valueAfterReset = 6;
//     int* newPtr = new int{valueAfterReset};

//     ptr.reset(newPtr);

//     ASSERT_EQ(*ptr, valueAfterReset);
// }

// TEST(SharedPtrArrowOperator, shouldUseArrowOperator) {
//     my::shared_ptr<A> ptr(new A{});

//     ASSERT_EQ(ptr->foo(), initialValue);
// }

// TEST_F(SharedPtrTest, shouldCreateSharedPtrFromWeakPtr) {
//     my::weak_ptr<int> wptr{ptr};

//     my::shared_ptr<int> sptr{wptr};

//     ASSERT_EQ(sptr.get(), ptr.get());
// }
