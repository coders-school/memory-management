#pragma once

#include <stdexcept>

template <typename T>
class unique_ptr {
public:
    unique_ptr(T* ptr);
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& otherPtr);
    ~unique_ptr();

    unique_ptr<T>& operator=(unique_ptr<T>&) = delete;
    unique_ptr<T>& operator=(unique_ptr<T>&& otherPtr);

    T& operator*() const;
    T* operator->() const;
    T* get() const;
    T* release();
    void reset(T* newPtr = nullptr);

private:
    T* ptr_;
};

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr)
    : ptr_(ptr) {}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& otherPtr) {
        ptr_ = otherPtr.release();
    }

template <typename T>
unique_ptr<T>::~unique_ptr() {
    delete ptr_;
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& otherPtr) {
    delete ptr_;
    ptr_ = otherPtr.release();
    return *this;
}

template <typename T>
T& unique_ptr<T>::operator*() const {
    return *ptr_;
}

template <typename T>
T* unique_ptr<T>::operator->() const {
    return ptr_;
}

template <typename T>
T* unique_ptr<T>::get() const {
    if (!ptr_) {
        return nullptr;
    }
    return ptr_;
}

template <typename T>
T* unique_ptr<T>::release() {
    T* tempPtr = ptr_;
    ptr_ = nullptr;
    return tempPtr;
}

template <typename T>
void unique_ptr<T>::reset(T* newPtr) {
    delete ptr_;
    ptr_ = newPtr;
}