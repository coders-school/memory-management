#pragma once

#include <stdexcept>
#include <string>

class NullptrException : public std::runtime_error {
public:
    NullptrException(std::string msg);
};