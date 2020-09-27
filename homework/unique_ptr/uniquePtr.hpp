#pragma once

#include "InvalidDereference.hpp"

namespace coders_school {

template <typename T>
class unique_ptr {
public:
    unique_ptr();
    unique_ptr(T* ptr);
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& otherPtr);
    ~unique_ptr();

    unique_ptr& operator=(const unique_ptr&) = delete;
    unique_ptr& operator=(unique_ptr&& otherPtr);
    T& operator*() const;
    T* operator->() const;

    T* get() const;
    T* release();
    void reset(T* newPtr = nullptr);

private:
    T* ptr_;
};

template <typename T>
unique_ptr<T>::unique_ptr()
    : ptr_(nullptr) {}

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr)
    : ptr_(ptr) {}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& otherPtr)
    : ptr_(otherPtr.release()) {}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    delete ptr_;
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& otherPtr) {
    if (this != &otherPtr) {
        delete ptr_;
        ptr_ = otherPtr.ptr_;
        otherPtr.ptr_ = nullptr;
    }

    return *this;
}

template <typename T>
T& unique_ptr<T>::operator*() const {
    if (!ptr_) {
        throw InvalidDereference("You can not dereference nullptr!");
    }

    return *ptr_;
}

template <typename T>
T* unique_ptr<T>::operator->() const {
    return ptr_;
}

template <typename T>
T* unique_ptr<T>::get() const {
    return ptr_;
}

template <typename T>
T* unique_ptr<T>::release() {
    T* tmpPtr = nullptr;
    std::swap(tmpPtr, ptr_);

    return tmpPtr;
}

template <typename T>
void unique_ptr<T>::reset(T* newPtr) {
    delete ptr_;
    ptr_ = newPtr;
}

}  // namespace