#pragma once

#include <stdexcept>

class InvalidDereference : public std::logic_error {
public:
    InvalidDereference(const std::string& errorMessage);
};