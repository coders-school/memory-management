#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../UniquePointer.hpp"

class TestObject {
public:
    TestObject() = default;
    ~TestObject() { Destructor(); }

    MOCK_METHOD(void, Destructor, (), (noexcept));
};

TEST(unique_ptr, destructor_test) {
    auto ptr = new TestObject();
    auto smartPtr = UniquePointer<TestObject>(ptr);

    EXPECT_CALL(*ptr, Destructor).Times(1);
}

TEST(unique_ptr, get_test) {
    auto ptr = new int{ 5 };
    auto smartPtr = UniquePointer<int>(ptr);

    EXPECT_EQ(ptr, smartPtr.get());
}

TEST(unique_ptr, reset_test) {
    auto ptr = new int{ 5 };
    auto smartPtr = UniquePointer<int>(ptr);

    smartPtr.reset(nullptr);
    EXPECT_EQ(nullptr, smartPtr.get());

    auto otherPtr = new int{ 6 };
    smartPtr.reset(otherPtr);
    EXPECT_EQ(otherPtr, smartPtr.get());
}

