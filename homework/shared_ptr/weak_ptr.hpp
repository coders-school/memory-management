#pragma once
#include <atomic>
#include "shared_ptr.hpp"

namespace my {

template <typename T>
class weak_ptr {
public:
    weak_ptr() noexcept;
    weak_ptr(shared_ptr<T>& other) noexcept;

    T& operator*() const noexcept;
    T* get() const noexcept;

private:
    T* ptr_;
    controlBlock* ptrToControlBlock_;
};

template <typename T>
weak_ptr<T>::weak_ptr() noexcept
    : ptr_(nullptr), ptrToControlBlock_(nullptr) {
}

template <typename T>
weak_ptr<T>::weak_ptr(shared_ptr<T>& other) noexcept {
    ptr_ = other.get();
    ptrToControlBlock_ = other.getControlBlockPtr();
}

template <typename T>
T& weak_ptr<T>::operator*() const noexcept {
    return *ptr_;
}

template <typename T>
T* weak_ptr<T>::get() const noexcept {
    return ptr_;
}

}  // namespace my
