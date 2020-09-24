#include "gtest/gtest.h"
#include "unique_ptr.hpp"

TEST(unique, canBeDefaultCreated) {
    cs::unique_ptr<int> ptr{};
}

TEST(unique, canBeCreatedWithValue) {
    cs::unique_ptr<int> ptr{new int{3}};
}

TEST(unique, canBeMovedByCtor) {
    cs::unique_ptr<int> ptr{cs::unique_ptr<int>(new int{3})};
    cs::unique_ptr<int> ptr2{std::move(ptr)};
}

TEST(unique, canBeMovedByMoveOperator) {
    cs::unique_ptr<int> ptr{new int{3}};
    cs::unique_ptr<int> ptr2 = std::move(ptr);
}

TEST(unique, canBeDereferenced) {
    cs::unique_ptr<int> ptr{new int{3}};
    EXPECT_EQ(*ptr, 3);
}

TEST(unique, arrowOperatorCanBeUsed) {
    struct foo {
        void use(){};
    };
    cs::unique_ptr<foo> ptr{new foo()};
    ptr->use();
    
}

TEST(unique, getMethodShouldReturnPointerWithoutReleasingOwnership) {
    cs::unique_ptr<int> ptr{new int{5}};
    int* raw_ptr = ptr.get();
    EXPECT_EQ(*ptr, *raw_ptr);
}
