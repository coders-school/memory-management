#pragma once

#include <type_traits>

template <class T>
class UniquePointer {
public:
    UniquePointer(T* pointer);
    ~UniquePointer();
    T operator*();

private:
    T* pointer_;
};

template <class T>
UniquePointer<T>::UniquePointer(T* pointer)
    : pointer_(pointer)
{
}

template <class T>
UniquePointer<T>::~UniquePointer()
{
    if (std::is_scalar<T>::value) {
        delete pointer_;
    }
    else {
        delete[] pointer_;
    }
}

template <class T>
T UniquePointer<T>::operator*()
{
    return *pointer_;
}
