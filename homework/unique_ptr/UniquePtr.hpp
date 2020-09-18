#pragma once

#include "NullptrException.hpp"

template <typename T>
class UniquePtr {
public:
    UniquePtr()
        : ptr_(nullptr) {}
    UniquePtr(T* ptr)
        : ptr_(ptr) {}

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& movedPtr);

    ~UniquePtr();

    T& operator=(const T&) = delete;
    T* operator->() const { return ptr_; }
    T& operator*() const;

    T* get() const { return ptr_; }
    T* release();
    void reset(T* newPtr);

private:
    T* ptr_;
};

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& movedPtr) {
    ptr_ = movedPtr.release();
}

template <typename T>
UniquePtr<T>::~UniquePtr() {
    if (ptr_) {
        delete ptr_;
    }
}

template <typename T>
T& UniquePtr<T>::operator*() const {
    if (!ptr_) {
        throw NullptrException("pointer is null");
    }
    return *ptr_;
}

template <typename T>
T* UniquePtr<T>::release() {
    T* res = nullptr;
    std::swap(res, ptr_);
    return res;
}

template <typename T>
void UniquePtr<T>::reset(T* newPtr) {
    if (ptr_) {
        delete ptr_;
    }
    ptr_ = newPtr;
}
