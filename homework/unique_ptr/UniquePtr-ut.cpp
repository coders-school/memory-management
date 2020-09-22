#include <string>
#include <vector>
#include "UniquePtr.hpp"
#include "gtest/gtest.h"

TEST(UniquePtrSuite, UniquePtrDereferencing) {
    auto ptr = UniquePtr<std::string>(new std::string("hello"));

    ASSERT_EQ("hello", *ptr);
}

TEST(UniquePtrSuite, UniquePointerReset) {
    int expectedValue = 200;
    auto ptr = UniquePtr<int>(new int(100));
    ptr.reset(new int(expectedValue));

    ASSERT_EQ(expectedValue, *ptr);
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
    ASSERT_FALSE(ptr.get());
}

TEST(UniquePtrSuite, UniquePointerArrowOperator) {
    std::pair<size_t, size_t> expectedValue(10, 20);
    auto ptr =
      UniquePtr<std::pair<size_t, size_t>>(new std::pair<size_t, size_t>{expectedValue});
    auto secondPtr =
        UniquePtr<std::pair<size_t, size_t>>(new std::pair<size_t, size_t>(30, 40));
    secondPtr = std::move(ptr);

    ASSERT_EQ(secondPtr->first, expectedValue.first);
    ASSERT_EQ(secondPtr->second, expectedValue.second);
    ASSERT_FALSE(ptr.get());
}
