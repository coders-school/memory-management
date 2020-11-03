#include "Exceptions.hpp"

InvalidDereference::InvalidDereference(const std::string& arg)
    : std::runtime_error(arg) {}
