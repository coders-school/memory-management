#include "gtest/gtest.h"
#include "UniquePtr.hpp"
#include <string>
#include <iostream>

// Jest klasą szablonową
// Trzyma wskaźnik do zarządzanego obiektu
// Konstruktor kopiuje wskaźnik
// Destruktor zwalnia pamięć
// Kopiowanie jest niedozwolone
// Przenoszenie jest dozwolone i oznacza:
//     Skopiowanie wskaźnika z obiektu źródłowego
//     Ustawienie wskaźnika w obiekcie źródłowym na nullptr
// Wymagane metody: operator*(), operator->(), get(), release(), reset()
// Nie zapomnij o testach (pokrycie >90%)

class testClassOperatorsAndFunctions {
public:
    testClassOperatorsAndFunctions(int value) : value_(value) {

    }

    int getValue() { return value_; }

private:
    int value_ { };
};

struct UniquePtrTest : public ::testing::Test {
    UniquePtr<int>uniqueTestNull;
    UniquePtr<int>uniqueTestValueInt{ new int(5) };
    UniquePtr<std::string>uniqueTestValueString{ new std::string("TEST") };
    UniquePtr<double>uniqueTestValueDouble{ new double(3.14) };
    UniquePtr<testClassOperatorsAndFunctions>uniqueTestArrowOperator{ new testClassOperatorsAndFunctions(999) };
};

TEST_F(UniquePtrTest, callNewObjectShouldReturnNullptr) {
    auto expected = nullptr;
    ASSERT_EQ(uniqueTestNull.get(), expected);
}

TEST_F(UniquePtrTest, assignValueShouldReturnValueInt) {
    auto expected = 5;
    ASSERT_EQ(*uniqueTestValueInt.get(), expected);
}

TEST_F(UniquePtrTest, assignValueShouldReturnValueString) {
    auto expected = "TEST";
    ASSERT_EQ(*uniqueTestValueString.get(), expected);
}

TEST_F(UniquePtrTest, assignValueShouldReturnValueDouble) {
    auto expected = 3.14;
    ASSERT_EQ(*uniqueTestValueDouble.get(), expected);
}

TEST_F(UniquePtrTest, usingGetValueShouldReturnRightValueInt) {
    auto expected = 999;
    ASSERT_EQ(uniqueTestArrowOperator->getValue(), expected);
}

TEST_F(UniquePtrTest, usingMoveConstructorShouldReturnRightValueInt) {
    auto expected = 5;
    auto newObject = std::move(uniqueTestValueInt);
    ASSERT_EQ(*newObject.get(), expected);
}

TEST_F(UniquePtrTest, usingMoveOperatorShouldReturnRightValueInt) {
    auto expected = 5;
    UniquePtr<int>newObject;
    newObject = std::move(uniqueTestValueInt);
    ASSERT_EQ(*newObject.get(), expected);
}

TEST_F(UniquePtrTest, usingReleaseShouldReleasePointer) {
    auto expected = 5;
    UniquePtr<int>newObjectRelease(new int(expected));
    UniquePtr<int>newObject(new int(expected));
    newObjectRelease.release();
    ASSERT_NE(newObject.get(), newObjectRelease.get());
}

TEST_F(UniquePtrTest, usingResetShouldResetPointer) {
    auto expected = 5;
    int* ptrTest = new int(10);
    UniquePtr<int>newObjectRelease(new int(expected));
    newObjectRelease.reset(ptrTest);
    ASSERT_EQ(*newObjectRelease.get(), *ptrTest);
}

TEST_F(UniquePtrTest, usingNullptrShouldCallException) {
    ASSERT_THROW(*uniqueTestNull, std::runtime_error);
}