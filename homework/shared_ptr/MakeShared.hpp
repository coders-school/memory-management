#pragma once

#include <utility>
#include "SharedPointer.hpp"

template <typename T, typename... Args>
SharedPointer<T> MakeShared(Args&&... args) {
    return SharedPointer<T>(new ControlBlockData<T>(std::forward<decltype(args)>(args)...));
}
