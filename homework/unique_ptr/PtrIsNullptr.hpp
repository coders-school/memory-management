#pragma once

#include <stdexcept>
#include <string>

class PtrIsNullptr : public std::runtime_error {
public:
    PtrIsNullptr()
        : std::runtime_error("Pointer is nullptr!!!") {}
};
