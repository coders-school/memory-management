#include "TestingClass.hpp"


TestingClass::TestingClass(std::string text)
    : text_{text} {}

TestingClass::TestingClass()
    : text_{lValueChecker} {}

TestingClass::TestingClass(const TestingClass&)
    : TestingClass() {}

TestingClass::TestingClass(TestingClass&&)
    : text_{rValueChecker} {}

TestingClass& TestingClass::operator=(const TestingClass&)
{
    text_ = lValueChecker;
    return *this;
}

TestingClass& TestingClass::operator=(TestingClass&&)
{
    text_ = rValueChecker;
    return *this;
}

std::string TestingClass::testingGetter() const
{
    return text_;
}

std::string TestingClass::lValueChecker = "Parametr for l value";
std::string TestingClass::rValueChecker = "Parametr for r value";