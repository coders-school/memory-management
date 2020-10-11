#pragma once

#include <utility>
#include "SharedPointer.hpp"

template <class T, class... Args>
SharedPointer<T> MakeShared(Args&&... args)
{
    return SharedPointer<T>(new T(std::forward<Args>(args)...));
}