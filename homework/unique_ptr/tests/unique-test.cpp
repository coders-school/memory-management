#include "gtest/gtest.h"
#include "unique_ptr.hpp"

class unique : public ::testing::Test {
   protected:
    int default_value{3};
};

TEST_F(unique, canBeDefaultCreated) {
    cs::unique_ptr<int> ptr{};
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(unique, canBeCreatedWithValue) {
    cs::unique_ptr<int> ptr{new int{default_value}};
    EXPECT_EQ(*ptr, default_value);
}

TEST_F(unique, canBeMovedByCtor) {
    cs::unique_ptr<int> ptr{cs::unique_ptr<int>(new int{default_value})};
    cs::unique_ptr<int> ptr2{std::move(ptr)};
    EXPECT_EQ(*ptr2, default_value);
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(unique, canBeMovedByMoveOperator) {
    cs::unique_ptr<int> ptr{new int{default_value}};
    cs::unique_ptr<int> ptr2 = std::move(ptr);
    EXPECT_EQ(*ptr2, default_value);
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(unique, canBeDereferenced) {
    cs::unique_ptr<int> ptr{new int{default_value}};
    EXPECT_EQ(*ptr, default_value);
}

TEST_F(unique, arrowOperatorCanBeUsed) {
    struct foo {
        void use(){};
    };
    cs::unique_ptr<foo> ptr{new foo()};
    ptr->use();
}

TEST_F(unique, getMethodShouldReturnPointerWithoutReleasingOwnership) {
    cs::unique_ptr<int> ptr{new int{default_value}};
    int* raw_ptr = ptr.get();
    EXPECT_EQ(*ptr, *raw_ptr);
    EXPECT_EQ(*raw_ptr,  default_value);
}

TEST_F(unique, releaseMethodShouldReturnPointerAndReleaseOwnership) {
    cs::unique_ptr<int> ptr{new int{default_value}};
    int* new_owner_ptr = ptr.release();
    EXPECT_EQ(ptr.get(), nullptr);
    delete new_owner_ptr;
}

TEST_F(unique, resetMethodShouldSetAsNullptrByDefault) {
    cs::unique_ptr<int> ptr{new int{default_value}};
    ptr.reset();
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(unique, resetMethodShouldSetPtrAsEqualToArgument) {
    cs::unique_ptr<int> ptr{new int{default_value}};
    int new_value{10};
    ptr.reset(new int{new_value});
    EXPECT_EQ(*ptr, new_value);
}

TEST_F(unique, resetShouldSetOwnershipAgain) {
    cs::unique_ptr<int> ptr{new int{default_value}};
    delete ptr.release();
    int new_value{10};
    ptr.reset(new int{new_value});
    EXPECT_EQ(*ptr, new_value);
}

TEST_F(unique, moveWhenUniqueAlreadyOwnsPtr) {
    cs::unique_ptr<int> ptr{new int{default_value}};
    int new_value{10};
    ptr = cs::unique_ptr<int>(new int{new_value});
    EXPECT_EQ(*ptr, new_value);
    cs::unique_ptr<int> toBeMoved{new int{default_value}};
    ptr = std::move(toBeMoved);
    EXPECT_EQ(*ptr, default_value);
}
