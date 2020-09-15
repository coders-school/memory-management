#include <string>
#include "gtest/gtest.h"
#include "unique_ptr.hpp"

TEST(PointerTest, ShouldProperlyDereference) {
    cs::unique_ptr<std::string> testPointer(new std::string{"Ala ma kota"});
    auto stringToCompare = *testPointer;
    std::string testString{"Ala ma kota"};

    ASSERT_EQ(stringToCompare, *testPointer);
}
TEST(PointerTest, ShouldProperlyReturnPointerViaGet) {
    cs::unique_ptr<std::string> testPointer(new std::string{"Ala ma kota"});
    auto ptr = testPointer.get();
    ASSERT_EQ(ptr, testPointer.get());
}
TEST(PointerTest, ShouldProperlyReset) {
    cs::unique_ptr<std::string> testPointer(new std::string{"Ala ma kota"});
    std::string valueToResetTo{"Kota ma Ale"};
    testPointer.reset(new std::string(valueToResetTo));

    ASSERT_EQ(valueToResetTo, *testPointer);
}
TEST(PointerTest, ShouldProperlyMovePointer) {
    cs::unique_ptr<std::string> testPointerToBeMoved(new std::string{"Ala ma kota"});
    std::string valueMoved{"Ala ma kota"};
    cs::unique_ptr<std::string> testPointer(std::move(testPointerToBeMoved));

    ASSERT_EQ(valueMoved, *testPointer);
}

TEST(PointerTest, MovedPointerShouldBeNullptr) {
    cs::unique_ptr<std::string> testPointerToBeMoved(new std::string{"Ala ma kota"});
    cs::unique_ptr<std::string> testPointer(std::move(testPointerToBeMoved));

    ASSERT_EQ(nullptr, testPointerToBeMoved.get());
}

TEST(PointerTest, ShouldProperlyUseArrowOperator) {
    cs::unique_ptr<std::string> testPointer(new std::string{"Ala ma kota"});
    std::string testString{"Ala ma kota"};

    ASSERT_EQ(testPointer->at(1), testString.at(1));
}

TEST(PointerTest, DereferencingANullptrShouldThrowAnExeption) {
    cs::unique_ptr<int> testPointer(nullptr);
    EXPECT_ANY_THROW(*testPointer);
}
