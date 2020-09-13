#pragma once

template <typename T>
class unique_ptr {
public:
    unique_ptr(T* ptr);
private:
    T* ptr_;
};

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr)
    : ptr_(ptr) {}
