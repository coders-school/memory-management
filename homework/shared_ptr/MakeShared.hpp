#pragma once

#include "SharedPointer.hpp"

template <class T>
SharedPointer<T> MakeShared(T object)
{
    SharedPointer<T> ptr(new decltype(object){object});
    return ptr;
}


/*

[data] [shared refs] [weak refs] [deleter]

/*