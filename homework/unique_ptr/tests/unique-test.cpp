#include "gtest/gtest.h"
#include "unique_ptr.hpp"

TEST(unique, canBeDefaultCreated) {
    cs::unique_ptr<int> ptr{};
}

TEST(unique, canBeCreatedWithValue) {
    cs::unique_ptr<int> ptr{new int{3}};
}

TEST(unique, canBeMoved) {
    cs::unique_ptr<int> ptr{cs::unique_ptr<int>(new int{3})};
    cs::unique_ptr<int> ptr2{std::move(ptr)};
}


