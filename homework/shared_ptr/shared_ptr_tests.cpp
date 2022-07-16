#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <utility>
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

template class my::shared_ptr<int>;

TEST(SharedPtrTest, InitTest) {
    my::shared_ptr<uint8_t> ptr1{nullptr};
    ASSERT_EQ(ptr1.get(), nullptr);

    my::shared_ptr ptr2{new MockDummy};
    ASSERT_NE(ptr2.get(), nullptr);

    auto* raw_ptr3 = new MockDummy;
    my::shared_ptr ptr3{raw_ptr3};
    ASSERT_EQ(ptr3.get(), raw_ptr3);
}

TEST(SharedPtrTest, CopyTest) {
    my::shared_ptr ptr1{new MockDummy};
    ASSERT_EQ(ptr1.use_count(), 1);
    my::shared_ptr ptr2{ptr1};
    ASSERT_EQ(ptr1.use_count(), 2);
    ASSERT_EQ(ptr2.use_count(), 2);
    ASSERT_EQ(ptr1.get(), ptr2.get());
    {
        my::shared_ptr<MockDummy> ptr3{nullptr};
        ptr3 = ptr2;
        ASSERT_EQ(ptr1.use_count(), 3);
        ASSERT_EQ(ptr2.use_count(), 3);
        ASSERT_EQ(ptr3.use_count(), 3);
        ASSERT_EQ(ptr3.get(), ptr2.get());
    }
    ASSERT_EQ(ptr1.use_count(), 2);
    ASSERT_EQ(ptr2.use_count(), 2);
    ptr1 = ptr2;
    ASSERT_EQ(ptr1.use_count(), 2);
    ASSERT_EQ(ptr2.use_count(), 2);
}

TEST(SharedPtrTest, MoveTest) {
    my::shared_ptr ptr1{new MockDummy};
    ASSERT_EQ(ptr1.use_count(), 1);
    DummyClass* helper_ptr = ptr1.get();
    my::shared_ptr ptr2{std::move(ptr1)};
    ASSERT_EQ(ptr1.use_count(), 1);
    ASSERT_EQ(ptr2.use_count(), 1);
    ASSERT_EQ(ptr1.get(), nullptr);
    ASSERT_EQ(ptr2.get(), helper_ptr);
    my::shared_ptr<MockDummy> ptr3{new MockDummy};
    ptr3 = std::move(ptr2);
    ASSERT_EQ(ptr2.get(), nullptr);
    ASSERT_EQ(ptr3.get(), helper_ptr);
    ASSERT_EQ(ptr2.use_count(), 1);
    ASSERT_EQ(ptr3.use_count(), 1);
}

TEST(SharedPtrTest, ResetTest) {
    my::shared_ptr ptr1{new MockDummy};
    ASSERT_NE(ptr1.get(), nullptr);
    ptr1.reset();
    ASSERT_EQ(ptr1.get(), nullptr);
    auto* helper_ptr = new MockDummy;
    ptr1.reset(helper_ptr);
    ASSERT_EQ(helper_ptr, ptr1.get());
    ASSERT_EQ(ptr1.use_count(), 1);
    ptr1.reset(new MockDummy, [](MockDummy* ptr) { delete ptr; });
    ASSERT_NE(ptr1.get(), nullptr);
    ASSERT_EQ(ptr1.use_count(), 1);
}

TEST(SharedPtrTest, CustomDeleterTest) {
    {
        auto* mocked_ptr = new MockDummy;
        EXPECT_CALL(*mocked_ptr, simpleMethod()).Times(1);
        {
            my::shared_ptr<MockDummy> ptr1{mocked_ptr, [](MockDummy* ptr) { ptr->simpleMethod(); delete ptr; }};
        }
    }
    {
        auto* mocked_ptr1 = new MockDummy;
        auto* mocked_ptr2 = new MockDummy;
        EXPECT_CALL(*mocked_ptr1, simpleMethod()).Times(1);
        EXPECT_CALL(*mocked_ptr2, callMe(42)).Times(1);
        {
            my::shared_ptr<MockDummy> ptr1{mocked_ptr1, [](MockDummy* ptr) { ptr->simpleMethod(); delete ptr; }};
            ptr1.reset(mocked_ptr2, [](MockDummy* ptr) { ptr->callMe(42); delete ptr; });
        }
    }
}
