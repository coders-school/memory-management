#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include "make_shared.hpp"
#include "shared_ptr.hpp"

class DummyClass {
public:
    virtual ~DummyClass() = default;
    virtual void simpleMethod() = 0;
    virtual int callMe(int num) = 0;
};

class MockDummy : public DummyClass {
public:
    MOCK_METHOD(void, simpleMethod, (), (override));
    MOCK_METHOD(int, callMe, (int num), (override));
};

TEST(MakeSharedTest, InitTest) {
    my::shared_ptr<int> ptr1 = my::make_shared<int>(1);
    ASSERT_EQ(*ptr1, 1);
}
