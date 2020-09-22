#pragma once

#include <utility>

template <class T>
class unique_ptr {
private:
    T* ptr_;

public:
    unique_ptr(T* newPtr = nullptr);
    unique_ptr(unique_ptr<T>&& otherPtr);
    ~unique_ptr();

    T* get() const;
    T* release();
    void reset(T* newPtr = nullptr);

    T& operator*() const;
    T& operator->() const;
    unique_ptr<T>& operator=(unique_ptr<T>&& otherPtr);

    unique_ptr(const unique_ptr<T>& otherPtr) = delete;
    unique_ptr<T>& operator=(const unique_ptr<T>& otherPtr) = delete;
};

template <class T>
unique_ptr<T>::unique_ptr(T* newPtr)
    : ptr_(newPtr) {}

template <class T>
unique_ptr<T>::~unique_ptr() {
    delete ptr_;
}

template <class T>
unique_ptr<T>::unique_ptr(unique_ptr<T>&& otherPtr) {
    ptr_ = otherPtr.ptr_;
    otherPtr.ptr_ = nullptr;
}

template <class T>
T* unique_ptr<T>::get() const {
    return ptr_;
}

template <class T>
T* unique_ptr<T>::release() {
    T* tmpPtr = ptr_;
    ptr_ = nullptr;
    return tmpPtr;
}

template <class T>
void unique_ptr<T>::reset(T* newPtr) {
    delete ptr_;
    ptr_ = newPtr;
}

template <class T>
T& unique_ptr<T>::operator*() const {
    return *ptr_;
}

template <class T>
T& unique_ptr<T>::operator->() const {
    return *ptr_;
}

template <class T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& otherPtr) {
    if (this != &otherPtr) {
        delete ptr_;
        ptr_ = otherPtr.ptr_;
        otherPtr.ptr_ = nullptr;
    }
    return *this;
}
