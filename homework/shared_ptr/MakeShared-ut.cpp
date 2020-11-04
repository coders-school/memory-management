#include <gtest/gtest.h>

#include "MakeShared.hpp"
#include "SharedPtr.hpp"

int initValue = 5;
constexpr int newValue = 10;

TEST(MakeSharedPtrTest, ShouldDereferenceSharedPtr) {
    cs::SharedPtr<int> someInt(new int{42});
    auto intPtr = new int{42};
    auto makeSomeInt = cs::makeShared<int>(intPtr);
    // auto makeSomeInt = cs::makeShared<int>(initValue);
    ASSERT_EQ(*makeSomeInt, *someInt);
}
