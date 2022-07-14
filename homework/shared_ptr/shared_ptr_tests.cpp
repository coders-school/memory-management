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
