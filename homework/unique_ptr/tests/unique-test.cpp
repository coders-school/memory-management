#include "gtest/gtest.h"
#include "unique_ptr.hpp"

TEST(unique, canBeCreated) {
    cs::unique_ptr<int> ptr{new int{3}};
}
