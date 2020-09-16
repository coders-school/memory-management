#pragma once

#include <iostream>
#include <stdexcept>

class DereferenceNullPtrError : public std::logic_error {
    DereferenceNullPtrError()
        : std::logic_error("Error - nullptr dereference") {}
};

template <typename T>
class UniquePtr {
public:
    UniquePtr();
    UniquePtr(T* ptr);
    ~UniquePtr();
    UniquePtr(const UniquePtr<T>& otherPtr) = delete;
    UniquePtr(UniquePtr<T>&& otherPtr);
    UniquePtr& operator=(const UniquePtr<T>& otherPtr) = delete;
    UniquePtr& operator=(UniquePtr<T>&& otherPtr);
    UniquePtr<T>& operator*() const;
    UniquePtr<T>* operator->() const;
    UniquePtr* get() const;
    UniquePtr* relese();
    void reset(UniquePtr* newPtr);

private:
    T* ptr_ = nullptr;
};

template <class T>
UniquePtr<T>::UniquePtr()
    : ptr_(nullptr) {}

template <typename T>
UniquePtr<T>::UniquePtr(T* ptr)
    : ptr_(ptr) {}

template <typename T>
UniquePtr<T>::~UniquePtr() {
    delete ptr_;
}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& otherPtr)
    : ptr_(otherPtr.ptr_.release()) {
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& otherPtr) {
    if (this != otherPtr) {
        if (ptr_ != nullptr) {
            delete ptr_;
        }
        ptr_ = otherPtr.ptr_.release();
    }
    return *this;
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator*() const {
    try {
        if (ptr_ == nullptr) {
            throw DereferenceNullPtrError();
        }
    } catch (DereferenceNullPtrError& error) {
        std::cerr << error.what() << "\n";
    }
    return *ptr_;
}

template <typename T>
UniquePtr<T>* UniquePtr<T>::operator->() const {
    return ptr_;
}

template <typename T>
UniquePtr<T>* UniquePtr<T>::get() const {
    return ptr_;
}
template <typename T>
UniquePtr<T>* UniquePtr<T>::relese() {
    UniquePtr<T>* tempPtr = ptr_;
    delete ptr_;
    ptr_ = nullptr;
    return tempPtr;
}

template <typename T>
void UniquePtr<T>::reset(UniquePtr<T>* newPtr) {
    if (ptr_ != nullptr) {
        delete ptr_;
    }
    ptr_ = newPtr;
}
