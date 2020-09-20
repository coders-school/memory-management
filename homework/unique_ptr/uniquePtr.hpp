#pragma once

#include <stdexcept>
#include <string>

class NullptrException : public std::runtime_error {
public:
    NullptrException() : std::runtime_error{"Pointer is nullptr.\n"} {}
};

template <typename T>
class unique_ptr {
public:
    unique_ptr();
    unique_ptr(T* ptr);
    unique_ptr(unique_ptr&& otherPtr);
    unique_ptr(const unique_ptr&) = delete;
    ~unique_ptr();

    T* get() const;
    T* release();
    void reset(T* newPtr = nullptr);

    T& operator*() const;
    T* operator->() const;
    unique_ptr& operator=(unique_ptr& otherPtr) = delete;
    unique_ptr& operator=(unique_ptr&& otherPtr);

private:
    T* ptr_;
};

template <typename T>
unique_ptr<T>::unique_ptr() : ptr_(nullptr) {}

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr) : ptr_(ptr) {}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& otherPtr) : ptr_(otherPtr.release()) {}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    delete ptr_;
}

template <typename T>
T* unique_ptr<T>::get() const {
    return ptr_;
}

template <typename T>
T* unique_ptr<T>::release() {
    T* temp = nullptr;
    std::swap(temp, ptr_);
    return temp;
}

template <typename T>
void unique_ptr<T>::reset(T* newPtr) {
    delete ptr_;
    ptr_ = newPtr;
}

template <typename T>
T& unique_ptr<T>::operator*() const {
    if (!ptr_) {
        throw NullptrException{};
    };
    return *ptr_;
}

template <typename T>
T* unique_ptr<T>::operator->() const {
    return ptr_;
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& otherPtr) {
    if (this != &otherPtr) {
        delete ptr_;
        ptr_ = otherPtr.ptr_;
        otherPtr.ptr_ = nullptr;
    }
    return *this;
}
