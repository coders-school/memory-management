#pragma once

#include "SharedPointer.hpp"

template <class T>
SharedPointer<T> MakeShared (T* address){
    SharedPointer<T> ptr (address);
    return ptr;
}