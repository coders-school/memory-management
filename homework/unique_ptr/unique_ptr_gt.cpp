#include "uniqe_ptr.hpp"

#include "gtest/gtest.h"


constexpr int expected = 100;
constexpr int newexpected = 200;

class UniquePtrTest : public ::testing::Test
{
public:
    UniquePtrTest() : ptr_(new int(expected)) {}
protected:
    uniqe_ptr<int>ptr_;
};

TEST_F(UniquePtrTest, ShouldDereferencePointer)
{
    EXPECT_EQ(*ptr_, expected);
}

TEST_F(UniquePtrTest,ShouldChangeValueTo200) {
    *ptr_ = newexpected;
    EXPECT_EQ(*ptr_, newexpected);
}

TEST_F(UniquePtrTest, ShouldCreatNullptr) {
    uniqe_ptr<int> null_ptr;
    ASSERT_EQ(null_ptr.get(), nullptr);
}

TEST_F(UniquePtrTest, ShouldResetPointer)
{
    ptr_.reset(new int(newexpected));
    ASSERT_EQ(*ptr_, newexpected);
    ptr_.reset();
    ASSERT_EQ(ptr_.get(), nullptr);
}

TEST_F(UniquePtrTest, ShouldReales) {
    auto ptr2 = ptr_.release();
    ASSERT_EQ(*ptr2, expected);
    ASSERT_EQ(ptr_.get(), nullptr);
    delete ptr2;
}

TEST_F(UniquePtrTest, ShouldMovePointerByOperator) {
    uniqe_ptr<int> ptr1{new int(expected)};
    uniqe_ptr<int> ptr2{new int(newexpected)};
    ptr2 = std::move(ptr1);
    ASSERT_EQ(ptr1.get(), nullptr);
    ASSERT_EQ(*ptr2, expected);
}

