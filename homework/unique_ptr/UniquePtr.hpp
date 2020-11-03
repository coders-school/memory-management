#pragma once

template <typename T>
class UniquePtr {
public:
    UniquePtr() = default;
    UniquePtr(T * rawPtr);
    UniquePtr(const UniquePtr<T> &) = delete;
    UniquePtr(UniquePtr<T> && otherPtr) noexcept;

private:
    T * rawPtr_ = nullptr;
};

template <typename T>
UniquePtr<T>::UniquePtr(T * rawPtr) : rawPtr_(rawPtr) {}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T> && otherPtr) noexcept 
    : rawPtr_(other.rawPtr_) {
        other.rawPtr_ = nullptr;
    }
