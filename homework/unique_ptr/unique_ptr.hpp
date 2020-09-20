#pragma once

#include "PtrIsNullptr.hpp"

template <typename T>
class unique_ptr {
public:
    unique_ptr() = default;
    unique_ptr(T* ptr)
        : ptr_(ptr) {}
    unique_ptr(const unique_ptr& otherPtr) = delete;
    unique_ptr(unique_ptr&& otherPtr)
        :ptr_(otherPtr.release()) {};

    ~unique_ptr();

    T* get() const { return ptr_; }
    T* release();
    void reset(T* newPtr);

    T& operator*() const;
    T* operator->() const { return ptr_; }
    
    unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;
    unique_ptr<T>& operator=(unique_ptr<T>&& otherPtr);

private:
    T* ptr_ = nullptr;
};

template <typename T>
T* unique_ptr<T>::release() {
    T* temp = ptr_;
    ptr_ = nullptr;
    return temp;
}

template <typename T>
void unique_ptr<T>::reset(T* newPtr) {
    delete ptr_;
    ptr_ = newPtr;
}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    delete ptr_;
}

template <typename T>
T& unique_ptr<T>::operator*() const {
    if (!ptr_) {
        throw PtrIsNullptr{};
    }
    return *ptr_;
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& otherPtr){
    delete ptr_;
    ptr_ = otherPtr.release();
    otherPtr.ptr_ = nullptr;
    return *this;
}
