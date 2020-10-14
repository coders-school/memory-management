#pragma once

#include <utility>
#include "SharedPointer.hpp"

// template <class T, class... Args>
// SharedPointer<T> MakeShared(Args&&... args)
// {
//     return SharedPointer<T>(new T(std::forward<Args>(args)...));
// }

// template <class T>
// SharedPointer<T> MakeShared(T value) {
//     return SharedPointer<T>(new ControlBlockData<T>(value));
// }

template <typename T, typename... Args>
SharedPointer<T> MakeShared(Args&&... args) {
    return SharedPointer<T>(new ControlBlockData<T>(std::forward<decltype(args)>(args)...));
}
