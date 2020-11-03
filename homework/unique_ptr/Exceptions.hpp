#pragma once
#include <stdexcept>
#include <string>

class InvalidDereference : public std::runtime_error {
public:
    InvalidDereference(const std::string& arg);
};
