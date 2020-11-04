#include "Exceptions.hpp"
#include "gtest/gtest.h"
#include "UniquePtr.hpp"

constexpr int testDistance = 50;
constexpr int newTestDistance = 100;

class Velocity {
    Velocity(int distance, int time) : distance_(distance), time_(time) {}

    int distance_ = 0; //in km
    int time_ = 1;     //in h
    int countVelocity() { return distance_ / time_; }
};

class UniquePointerTest : public ::testing::Test {
protected:
    UniquePointerTest() : uniqueIntPtr(new int{testDistance}) {}
    UniquePtr<int> uniqueIntPtr;
};

TEST_F(UniquePointerTest, ShouldDereferencePointerWhichIsNotANullptr) {
    ASSERT_EQ(*uniqueIntPtr, testDistance);
}

TEST_F(UniquePointerTest, ShouldUseReset) {
    uniqueIntPtr.reset(new int{newTestDistance});
    ASSERT_EQ(*uniqueIntPtr, newTestDistance);
}

TEST_F(UniquePointerTest, ShouldNotDereferenceANullptr) {
    uniqueIntPtr.reset(nullptr);
    ASSERT_THROW(*uniqueIntPtr, InvalidDereference);
}

TEST_F(UniquePointerTest, ShouldDereferenceAndChangeValue) {
    *uniqueIntPtr = newTestDistance;
    ASSERT_EQ(*uniqueIntPtr, newTestDistance);
}
