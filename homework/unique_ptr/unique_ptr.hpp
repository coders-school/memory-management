#pragma once

template <typename T>
class unique_ptr {
public:
    unique_ptr(T* ptr);
    ~unique_ptr();

private:
    T* ptr_;
};

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr)
    : ptr_(ptr) {}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    if (ptr_) {
        delete ptr_;
    }
}
