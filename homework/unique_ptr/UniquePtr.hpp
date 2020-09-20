#pragma once

#include <iostream>
#include <stdexcept>

class DereferenceNullPtrError : public std::logic_error {
public:
    DereferenceNullPtrError()
        : std::logic_error("Error - nullptr dereference") {}
};

template <typename T>
class UniquePtr {
public:
    UniquePtr<T>() = default;
    UniquePtr<T>(T* ptr);
    ~UniquePtr();
    UniquePtr(const UniquePtr& otherPtr) = delete;
    UniquePtr(UniquePtr&& otherPtr);
    UniquePtr& operator=(const UniquePtr& otherPtr) = delete;
    UniquePtr& operator=(UniquePtr&& otherPtr);
    T& operator*() const;
    T* operator->() const;
    T* get() const;
    T* release();
    void reset(T* newPtr = nullptr);

private:
    T* ptr_ = nullptr;
};

template <typename T>
UniquePtr<T>::UniquePtr(T* ptr)
    : ptr_(ptr) {}

template <typename T>
UniquePtr<T>::~UniquePtr() {
    delete ptr_;
}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& otherPtr)
    : ptr_(otherPtr.release()) {}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& otherPtr) {
    if (ptr_ != nullptr) {
        delete ptr_;
    }
    ptr_ = otherPtr.ptr_;
    otherPtr.ptr_ = nullptr;
    return *this;
}

template <typename T>
T& UniquePtr<T>::operator*() const {
    if (ptr_ == nullptr) {
        throw DereferenceNullPtrError();
    }
    return *ptr_;
}

template <typename T>
T* UniquePtr<T>::operator->() const {
    return ptr_;
}

template <typename T>
T* UniquePtr<T>::get() const {
    return ptr_;
}
template <typename T>
T* UniquePtr<T>::release() {
    T* tempPtr = ptr_;
    ptr_ = nullptr;
    return tempPtr;
}

template <typename T>
void UniquePtr<T>::reset(T* newPtr) {
    delete ptr_;
    ptr_ = newPtr;
}
