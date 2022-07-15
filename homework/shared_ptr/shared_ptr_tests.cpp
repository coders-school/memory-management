#include <gtest/gtest.h>
#include <iostream>
#include <utility>
#include "shared_ptr.hpp"

class DummyClass {
public:
    DummyClass() = default;
    void simpleMethod() {
        std::cout << "SimpleMethod\n";
    }
    int callMe(int num) {
        return num;
    }
};

template class my::shared_ptr<int>;

TEST(SharedPtrTest, InitTest) {
    my::shared_ptr<uint8_t> ptr1{nullptr};
    ASSERT_EQ(ptr1.get(), nullptr);

    my::shared_ptr ptr2{new DummyClass};
    ASSERT_NE(ptr2.get(), nullptr);

    auto* raw_ptr3 = new DummyClass;
    my::shared_ptr ptr3{raw_ptr3};
    ASSERT_EQ(ptr3.get(), raw_ptr3);
}

TEST(SharedPtrTest, CopyTest) {
    my::shared_ptr ptr1{new DummyClass};
    ASSERT_EQ(ptr1.use_count(), 1);
    my::shared_ptr ptr2{ptr1};
    ASSERT_EQ(ptr1.use_count(), 2);
    ASSERT_EQ(ptr2.use_count(), 2);
    ASSERT_EQ(ptr1.get(), ptr2.get());
    {
        my::shared_ptr<DummyClass> ptr3{nullptr};
        ptr3 = ptr2;
        ASSERT_EQ(ptr1.use_count(), 3);
        ASSERT_EQ(ptr2.use_count(), 3);
        ASSERT_EQ(ptr3.use_count(), 3);
        ASSERT_EQ(ptr3.get(), ptr2.get());
    }
    ASSERT_EQ(ptr1.use_count(), 2);
    ASSERT_EQ(ptr2.use_count(), 2);
}

TEST(SharedPtrTest, MoveTest) {
    my::shared_ptr ptr1{new DummyClass};
    ASSERT_EQ(ptr1.use_count(), 1);
    DummyClass* helper_ptr = ptr1.get();
    my::shared_ptr ptr2{std::move(ptr1)};
    ASSERT_EQ(ptr1.use_count(), 1);
    ASSERT_EQ(ptr2.use_count(), 1);
    ASSERT_EQ(ptr1.get(), nullptr);
    ASSERT_EQ(ptr2.get(), helper_ptr);
    my::shared_ptr<DummyClass> ptr3{new DummyClass};
    ptr3 = std::move(ptr2);
    ASSERT_EQ(ptr2.get(), nullptr);
    ASSERT_EQ(ptr3.get(), helper_ptr);
    ASSERT_EQ(ptr2.use_count(), 1);
    ASSERT_EQ(ptr3.use_count(), 1);
}
