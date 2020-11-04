#include "Exceptions.hpp"
#include "gtest/gtest.h"
#include "UniquePtr.hpp"

constexpr int testDistance = 50;
constexpr int newTestDistance = 100;

class Velocity {
public:
    Velocity(int distance, int time) : distance_(distance), time_(time) {}
    int countVelocity() { return distance_ / time_; }

protected:
    int distance_ = 0; //in km
    int time_ = 1;     //in h
};

class UniquePointerTest : public ::testing::Test {
protected:
    UniquePointerTest() : uniquePtr(new int{testDistance}) {}
    UniquePtr<int> uniquePtr;
};

TEST_F(UniquePointerTest, ShouldDereferencePointerWhichIsNotANullptr) {
    ASSERT_EQ(*uniquePtr, testDistance);
}

TEST_F(UniquePointerTest, ShouldUseReset) {
    uniquePtr.reset(new int{newTestDistance});
    ASSERT_EQ(*uniquePtr, newTestDistance);
}

TEST_F(UniquePointerTest, ShouldNotDereferenceANullptr) {
    uniquePtr.reset(nullptr);
    ASSERT_THROW(*uniquePtr, InvalidDereference);
}

TEST_F(UniquePointerTest, ShouldDereferenceAndChangeValue) {
    *uniquePtr = newTestDistance;
    ASSERT_EQ(*uniquePtr, newTestDistance);
}

TEST_F(UniquePointerTest, ShouldUseRelease) {
    auto releasedPtr = uniquePtr.release();
    ASSERT_EQ(uniquePtr.get(), nullptr);
}

TEST_F(UniquePointerTest, ShouldGetAPointer) {
    auto rawPtr = uniquePtr.get();
    ASSERT_EQ(rawPtr, uniquePtr.get());
}

TEST_F(UniquePointerTest, ShouldCallMethodByArrowOperator) {
    int otherDistance = 30;
    int otherTime = 2;
    UniquePtr<Velocity> VelocityPtr = new Velocity(otherDistance, otherTime);
    ASSERT_EQ(VelocityPtr->countVelocity(), otherDistance / otherTime);
}
