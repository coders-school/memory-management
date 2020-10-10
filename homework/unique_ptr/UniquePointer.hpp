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
    delete pointer_;
}

template <class T>
T UniquePointer<T>::operator*()
{
    return *pointer_;
}
