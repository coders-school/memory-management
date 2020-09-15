#include <string>
#include <vector>
#include "UniquePtr.hpp"
#include "gtest/gtest.h"

TEST(UniquePtrSuite, UniquePtrDereferencing) {
    auto ptr = UniquePtr<std::string>(new std::string("hello"));

    ASSERT_EQ("hello", *ptr);
}

TEST(UniquePtrSuite, UniquePointerReset) {
    auto ptr = UniquePtr<int>(new int(100));
    ptr.reset(new int(200));

    ASSERT_EQ(200, *ptr);
}

TEST(UniquePtrSuite, UniquePointerRelease) {
    auto ptr = UniquePtr<std::vector<std::string>>(
        new std::vector<std::string>{"hi", "bonjour", "priviet", "hola"});
    std::vector<std::string>* released = ptr.release();
    std::vector<std::string> expected = {"hi", "bonjour", "priviet", "hola"};

    ASSERT_EQ(expected, *released);
    ASSERT_FALSE(ptr.get());
    delete released;
}

TEST(UniquePtrSuite, UniquePointerMoveSemantics) {
    auto ptr = UniquePtr<int>(new int(10));
    UniquePtr<int> hello_3 = std::move(ptr);

    ASSERT_EQ(*hello_3, 10);
}
