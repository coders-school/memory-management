#include <gtest/gtest.h>
#include <iostream>
#include <utility>
#include "unique_ptr.hpp"

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

TEST(UniquePtrTest, InitTest) {
    my::unique_ptr<uint8_t> ptr1{nullptr};
    ASSERT_EQ(ptr1.get(), nullptr);

    my::unique_ptr ptr2{new DummyClass};
    ASSERT_NE(ptr2.get(), nullptr);

    auto* raw_ptr3 = new DummyClass;
    my::unique_ptr ptr3{raw_ptr3};
    ASSERT_EQ(ptr3.get(), raw_ptr3);
}

TEST(UniquePtrTest, MoveTest) {
    my::unique_ptr ptr1{new DummyClass};
    my::unique_ptr<DummyClass> ptr2{nullptr};
    auto helper_ptr = ptr1.get();

    // Move assignment operator
    ptr2 = std::move(ptr1);
    ASSERT_EQ(ptr2.get(), helper_ptr);
    ASSERT_EQ(ptr1.get(), nullptr);

    // Move constructor
    my::unique_ptr ptr3{std::move(ptr2)};
    ASSERT_EQ(ptr3.get(), helper_ptr);
    ASSERT_EQ(ptr2.get(), nullptr);
}

TEST(UniquePtrTest, CallTest) {
    constexpr int val{10};
    my::unique_ptr ptr{new DummyClass};
    ASSERT_EQ(ptr->callMe(val), val);
}

TEST(UniquePtrTest, DereferenceTest) {
    my::unique_ptr ptr1{new int(5)};
    auto helper_ptr = ptr1.get();

    ASSERT_EQ(*ptr1, *helper_ptr);
}

TEST(UniquePtrTest, ReleaseTest) {
    auto helper_ptr = new DummyClass;
    my::unique_ptr ptr{helper_ptr};
    auto released_ptr = ptr.release();

    ASSERT_EQ(released_ptr, helper_ptr);
    ASSERT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtrTest, ResetTest) {
    constexpr int val{10};
    my::unique_ptr ptr1{new int(1)};
    my::unique_ptr ptr2{new int(val)};
    auto helper_ptr = ptr2.get();
    ptr1.reset(std::move(ptr2));
    ASSERT_EQ(ptr1.get(), helper_ptr);
    ASSERT_EQ(*ptr1.get(), val);
    ASSERT_EQ(ptr2.get(), nullptr);

    my::unique_ptr ptr3{new int(1)};
    ptr3.reset(new int(val));
    ASSERT_EQ(*ptr3.get(), val);
}

TEST(UniquePtrTest, BoolOperatorTest) {
    my::unique_ptr ptr1 {new DummyClass};
    ASSERT_TRUE(ptr1);

    my::unique_ptr<DummyClass> ptr2 {nullptr};
    ASSERT_FALSE(ptr2);
}