#include "Exceptions.hpp"
#include "gtest/gtest.h"
#include "UniquePtr.hpp"

class Velocity {
    Velocity(int distance, int time) : distance_(distance), time_(time) {}

    int distance_ = 0; //in km
    int time_ = 0;     //in h
    int countVelocity() { return distance_ / time_; }
};

constexpr int testDistance = 50;
constexpr int testTime = 1;

class UniquePtrTest : public ::testing::Test {
protected:
    UniquePtrTest() : uniqueIntPtr(new int{testDistance}) {}
    UniquePtr<int> uniqueIntPtr;
};