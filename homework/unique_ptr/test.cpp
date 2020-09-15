#include <string>
#include "gtest/gtest.h"
#include "unique_ptr.hpp"

const std::string testString{"Ala ma kota"};

struct TestingPtr : ::testing::Test {
    TestingPtr()
        : ptr(new std::string("Ala ma kota")) {
    }

    cs::unique_ptr<std::string> ptr;
};

TEST_F(TestingPtr, ShouldProperlyDereference) {
    std::string testString{"Ala ma kota"};

    ASSERT_EQ(testString, *ptr);
}

TEST_F(TestingPtr, ShouldProperlyReturnPointerViaGet) {
    auto testPtr = ptr.get();
    ASSERT_EQ(testPtr, ptr.get());
}

TEST_F(TestingPtr, ShouldProperlyReset) {
    std::string valueToResetTo{"Kota ma Ale"};
    ptr.reset(new std::string(valueToResetTo));

    ASSERT_EQ(valueToResetTo, *ptr);
}

TEST_F(TestingPtr, ShouldProperlyMovePointer) {
    cs::unique_ptr<std::string> testPointer(std::move(ptr));

    ASSERT_EQ(testString, *testPointer);
}

TEST_F(TestingPtr, MovedPointerShouldBeNullptr) {
    cs::unique_ptr<std::string> testPointer(std::move(ptr));

    ASSERT_EQ(nullptr, ptr.get());
}

TEST_F(TestingPtr, ShouldProperlyUseArrowOperator) {
    ASSERT_EQ(ptr->at(1), testString.at(1));
}

TEST(PointerTest, DereferencingANullptrShouldThrowAnExeption) {
    cs::unique_ptr<int> testPointer(nullptr);
    EXPECT_ANY_THROW(*testPointer);
}
