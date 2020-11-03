#pragma once

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