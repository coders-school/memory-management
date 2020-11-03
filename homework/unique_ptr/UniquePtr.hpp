#pragma once
#include "Exceptions.hpp"

template <typename T>
class UniquePtr
{
public:
    UniquePtr() = default;
    UniquePtr(T * rawPtr);
    UniquePtr(UniquePtr<T> && otherPtr) noexcept;
    ~UniquePtr();

    UniquePtr(const UniquePtr<T> &) = delete;
    UniquePtr<T> & operator=(const UniquePtr<T> &) = delete;

    UniquePtr<T> & operator=(UniquePtr<T> && otherUniquePtr) noexcept;

    T & operator*() const;
    T * operator->() const;
    T * get() const;
    T * release();
    void reset(T * newPtr);

private:
    T * rawPtr_ = nullptr;
};

template <typename T>
UniquePtr<T>::UniquePtr(T * rawPtr) : rawPtr_(rawPtr) {}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T> && otherPtr) noexcept
    : rawPtr_(otherPtr.rawPtr_) {
        otherPtr.rawPtr_ = nullptr;
    }

template <typename T>
UniquePtr<T>::~UniquePtr() {
  delete rawPtr_;
}

template <typename T>
UniquePtr<T> & UniquePtr<T>::operator=(UniquePtr<T> && otherUniquePtr) noexcept {
    if (this != & otherUniquePtr) {
        delete rawPtr_;
        rawPtr_ = otherUniquePtr.rawPtr_;
        otherUniquePtr = nullptr;
    }
    return * this;
}

template <typename T>
T & UniquePtr<T>::operator*() const {
    if (ptr) {
        return * ptr_;
    } else {
        throw InvalidDereference("You can't dereference a null pointer.");
    }
}


template <typename T>
T * UniquePtr<T>::operator->() const {
    return rawPtr_;
}

template <typename T>
T * UniquePtr<T>::get() const {
    return rawPtr_;
}

template <typename T>
T * UniquePtr<T>::release() {
    T * released = nullptr;
    std::swap(released, ptr_);
    return released;
}

template <typename T>
void UniquePtr<T>::reset(T * newPtr) { 
    newPtr = nullptr;
}
