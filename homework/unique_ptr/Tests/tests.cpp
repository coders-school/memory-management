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
