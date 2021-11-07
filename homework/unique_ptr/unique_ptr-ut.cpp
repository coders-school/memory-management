#include <cstddef>
#include <gtest/gtest.h>
#include <stdexcept>
#include <type_traits>

#include "unique_ptr.hpp"

constexpr auto initial = 42u;
constexpr auto changed = 24u;

using Initial = decltype(initial);
using Changed = decltype(changed);

template <typename T>
class Clazz {
public:
    Clazz(T value) : value(value) {}
    auto getValue() {
        return value;
    };
private:
    T value;
};

/* fixture */
class UniquePtrTest : public ::testing::Test
{
public:
   UniquePtrTest() : ptr(new Clazz<Initial>(initial)) {}

protected:
   unique_ptr<Clazz<Initial>> ptr;
};

/* copy semantics */
TEST_F(UniquePtrTest, ShouldNotBeCopyConstructibleByUsingCopyConstructor)
{
    EXPECT_FALSE(std::is_copy_constructible<unique_ptr<Initial>>::value);
}

TEST_F(UniquePtrTest, ShouldNotBeCopyAssignableByUsingCopyAssignmentOperator)
{
    EXPECT_FALSE(std::is_copy_assignable<unique_ptr<Initial>>::value);
}

TEST_F(UniquePtrTest, ShouldBeCopiedUsingCopyAssignmentOperatorWithNullptr)
{
    ptr = nullptr;
    EXPECT_EQ(ptr.get(), nullptr);
}

/* move semantics */
TEST_F(UniquePtrTest, ShouldBeMoveConscructibleByUsingMoveConstructor)
{
    EXPECT_TRUE(std::is_move_constructible<unique_ptr<Initial>>::value);
}

TEST_F(UniquePtrTest, ShouldBeMoveAssignableByUsingMoveAssignmentOperator)
{
    EXPECT_TRUE(std::is_move_assignable<unique_ptr<Initial>>::value);
}

/* operator overloading */
TEST_F(UniquePtrTest, ShouldDereferencePointer)
{
    Clazz clazz = *ptr;
    EXPECT_EQ(clazz.getValue(), initial);
}

TEST_F(UniquePtrTest, ShouldNotDereferenceNullptrButThrowException)
{
    ptr = nullptr;
    EXPECT_THROW(*ptr, std::runtime_error);
}

TEST_F(UniquePtrTest, ShouldUseMemberAccessOperator)
{   
    EXPECT_EQ(ptr->getValue(), initial);
}

/* helper methods */
TEST_F(UniquePtrTest, ShouldGetRawPointer)
{
    auto raw = ptr.get();
    EXPECT_EQ(raw->getValue(), initial);
}

TEST_F(UniquePtrTest, ShouldReleasePointerOwnership)
{
    auto released = ptr.release();
    EXPECT_EQ(released->getValue(), initial);
    EXPECT_EQ(ptr.get(), nullptr);
    delete released;
}

TEST_F(UniquePtrTest, ShouldResetPointerToNullptr)
{
    ptr.reset();
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(UniquePtrTest, ShouldResetPointerToNewPointer)
{
    ptr.reset(new Clazz<Changed>(changed));
    EXPECT_EQ(ptr->getValue(), changed);
}
