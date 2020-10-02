#include "InvalidDereference.hpp"

InvalidDereference::InvalidDereference(const std::string& errorMessage)
    : std::logic_error(errorMessage) {}
