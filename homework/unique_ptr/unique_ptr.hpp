#pragma once

#include "PtrIsNullptr.hpp"

template <typename T>
class unique_ptr {
public:
    unique_ptr() = default;
    unique_ptr(T* ptr)
        : ptr_(ptr) {}
    unique_ptr(const unique_ptr& otherPtr) = delete;
    unique_ptr(unique_ptr&& otherPtr);

    ~unique_ptr();

    T* get() const { return ptr_; }
    T* release();
    void reset(T* newPtr);

    T& operator*() const;
    T* operator->() const { return ptr_; }

private:
    T* ptr_ = nullptr;
};

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& otherPtr) {
    ptr_ = otherPtr.release();
}

template <typename T>
T* unique_ptr<T>::release() {
    T* temp = ptr_;
    ptr_ = nullptr;
    return temp;
}

template <typename T>
void unique_ptr<T>::reset(T* newPtr) {
    if (ptr_) {
        delete ptr_;
    }
    ptr_ = newPtr;
}


template <typename T>
unique_ptr<T>::~unique_ptr() {
    if (ptr_) {
        delete ptr_;
    }
}

template <typename T>
T& unique_ptr<T>::operator*() const {
    if (!ptr_) {
        throw PtrIsNullptr{};
    }
    return *ptr_;
}