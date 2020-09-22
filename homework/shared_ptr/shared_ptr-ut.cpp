#include <gtest/gtest.h>

#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

constexpr int initialValue = 5;

struct A {
    int foo() { return initialValue; }
};

struct SharedPtrTest : ::testing::Test {
    SharedPtrTest()
        : ptr(new int{initialValue}) {}

    cs::shared_ptr<int> ptr;
};

TEST_F(SharedPtrTest, shouldDereferenceSharedPtr) {
    ASSERT_EQ(*ptr, initialValue);
}

TEST_F(SharedPtrTest, shouldCopySharedPtr) {
    auto ptr2(ptr);
    auto ptr3 = ptr;

    ASSERT_EQ(*ptr, *ptr2);
    ASSERT_EQ(*ptr, *ptr3);
}

TEST_F(SharedPtrTest, shouldMoveSharedPtr) {
    auto ptr2(std::move(ptr));
    ASSERT_EQ(*ptr2, initialValue);

    auto ptr3 = std::move(ptr2);
    ASSERT_EQ(*ptr3, initialValue);
}

TEST_F(SharedPtrTest, shouldReturnUseCount) {
    constexpr size_t numOfPtrs = 3;
    auto ptr2 = ptr;
    auto ptr3 = ptr;

    ASSERT_EQ(ptr.use_count(), numOfPtrs);
}

TEST_F(SharedPtrTest, shouldConvertSharedPtrToBool) {
    cs::shared_ptr<int> ptr2;

    ASSERT_TRUE(ptr);
    ASSERT_FALSE(ptr2);
}

TEST_F(SharedPtrTest, shouldResetSharedPtr) {
    ptr.reset();

    ASSERT_EQ(ptr.get(), nullptr);

    constexpr int valueAfterReset = 6;
    int* newPtr = new int{valueAfterReset};

    ptr.reset(newPtr);

    ASSERT_EQ(*ptr, valueAfterReset);
}

TEST(SharedPtrArrowOperator, shouldUseArrowOperator) {
    cs::shared_ptr<A> ptr(new A{});

    ASSERT_EQ(ptr->foo(), initialValue);
}

TEST_F(SharedPtrTest, shouldCreateSharedPtrFromWeakPtr) {
    cs::weak_ptr<int> wptr{ptr};

    cs::shared_ptr<int> sptr{wptr};

    ASSERT_EQ(sptr.get(), ptr.get());
}
