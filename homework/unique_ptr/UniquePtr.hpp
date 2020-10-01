#pragma once

#include <iostream>

struct NullPtrDereferenceException : public std::runtime_error {
    NullPtrDereferenceException()
        : std::runtime_error{"Fatal error, cannot dereference nullptr"} {}
};

template <typename T>
class UniquePtr {
public:
    UniquePtr(T* ptr);

    UniquePtr(const UniquePtr<T>&) = delete;
    UniquePtr<T>& operator=(const UniquePtr<T>&) = delete;

    UniquePtr(UniquePtr<T>&& ptr);
    UniquePtr<T>& operator=(UniquePtr<T>&& ptr);

    T& operator*() const;
    T* operator->() const;
    T* get();
    T* release();
    void reset(T* ptr);
    ~UniquePtr();

private:
    T* resource_;
};

template <typename T>
UniquePtr<T>::UniquePtr(T* ptr)
    : resource_(ptr) {
}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& ptr)
    : resource_(nullptr) {
    resource_ = ptr.resource_;
    ptr.resource_ = nullptr;
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& ptr) {
    if (this != &ptr) {
        delete resource_;
        resource_ = ptr.resource_;
        ptr.resource_ = nullptr;
    }
    return *this;
}

template <typename T>
T& UniquePtr<T>::operator*() const {
    if (!resource_) {
        throw NullPtrDereferenceException();
    }
    return *resource_;
}

template <typename T>
T* UniquePtr<T>::operator->() const {
    return resource_;
}

template <typename T>
T* UniquePtr<T>::get() {
    return resource_;
}

template <typename T>
T* UniquePtr<T>::release() {
    T* ptr = resource_;
    resource_ = nullptr;
    return ptr;
}

template <typename T>
void UniquePtr<T>::reset(T* ptr = nullptr) {
    delete resource_;
    resource_ = ptr;
}

template <typename T>
UniquePtr<T>::~UniquePtr() {
    delete resource_;
}
