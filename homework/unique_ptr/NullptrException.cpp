#include "NullptrException.hpp"

NullptrException::NullptrException(std::string msg)
    : std::runtime_error(msg) {}