#pragma once
#include <string>

class TestingClass {
public:
    TestingClass(std::string text);

    TestingClass();

    TestingClass(const TestingClass&);

    TestingClass(TestingClass&&);

    TestingClass& operator=(const TestingClass&);

    TestingClass& operator=(TestingClass&&);

    std::string testingGetter() const;

    static std::string lValueChecker;
    static std::string rValueChecker;

private:
    std::string text_{};
};
