#pragma once

#include <string>

class TestingClass {
public:
    TestingClass(std::string text)
        : text_(text) {}
    std::string testingGetter();

private:
    std::string text_{};
};

