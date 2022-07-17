#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

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

template class my::weak_ptr<int>;

TEST(SharedPtrTest, InitTest) {
    my::weak_ptr<uint8_t> ptr1;
    ASSERT_EQ(ptr1.use_count(), 0);
    ASSERT_EQ(ptr1.expired(), true);

    my::shared_ptr<int> ptr2{new int(1)};
    my::weak_ptr ptr3{ptr2};
    ASSERT_EQ(ptr3.use_count(), 1);
    ASSERT_EQ(ptr3.expired(), false);
}
