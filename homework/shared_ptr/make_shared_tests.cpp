#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include "make_shared.hpp"
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

TEST(MakeSharedTest, InitTest) {
    my::shared_ptr<int> ptr1 = my::make_shared<int>(1);
    ASSERT_EQ(*ptr1, 1);
    my::weak_ptr<int> ptr2{ptr1};
    ASSERT_EQ(*ptr2.lock(), *ptr1);
    ptr2.reset();
    ASSERT_EQ(ptr2.lock().get(), nullptr);
    int* helper_ptr = new int(3);
    ptr1.reset(helper_ptr);
    ASSERT_EQ(*ptr1, 3);

    my::shared_ptr<std::pair<int, int>> ptr3 = my::make_shared<std::pair<int, int>>(10, 20);
    ASSERT_EQ(ptr3->second, 20);
}

TEST(MakeSharedTest, MoveTest) {
    // intended to use with valgrind
    my::shared_ptr ptr1 = my::make_shared<MockDummy>();
    my::shared_ptr ptr2 = std::move(ptr1);
    ASSERT_EQ(ptr2.use_count(), 1);
}
