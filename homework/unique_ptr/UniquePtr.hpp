#pragma once
#include "Exceptions.hpp"

template <typename T>
class UniquePtr
{
public:
    UniquePtr() = default;
    UniquePtr(T * rawPtr);
    UniquePtr(UniquePtr<T> && otherPtr);
    ~UniquePtr();

    UniquePtr(const UniquePtr<T> &) = delete;
    UniquePtr<T> & operator=(const UniquePtr<T> &) = delete;

    UniquePtr<T> & operator=(UniquePtr<T> && otherUniquePtr);

    T & operator*() const;
    T * operator->() const;
    T * get() const;
    T * release();
    void reset(T * newPtr = nullptr);

private:
    T * rawPtr_ = nullptr;
};

template <typename T>
UniquePtr<T>::UniquePtr(T * rawPtr) : rawPtr_(rawPtr) {}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T> && otherPtr)
    : rawPtr_(otherPtr.rawPtr_) {
        otherPtr.rawPtr_ = nullptr;
    }

template <typename T>
UniquePtr<T>::~UniquePtr() {
  delete rawPtr_;
}

template <typename T>
UniquePtr<T> & UniquePtr<T>::operator=(UniquePtr<T> && uniquePtrToMove) {
    if (this != & uniquePtrToMove) {
        delete rawPtr_;
        rawPtr_ = uniquePtrToMove.rawPtr_;
        uniquePtrToMove.rawPtr_ = nullptr;
    }
    return * this;
}

template <typename T>
T & UniquePtr<T>::operator*() const {
    if (rawPtr_) {
        return * rawPtr_;
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
    std::swap(released, rawPtr_);
    return released;
}

template <typename T>
void UniquePtr<T>::reset(T * newPtr) { 
    delete rawPtr_;
    rawPtr_ = newPtr;
}
