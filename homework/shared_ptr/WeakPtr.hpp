#pragma once

#include "SharedControlBlock.hpp"
#include "SharedPtr.hpp"

template <typename T>
class WeakPtr {
public:
    constexpr WeakPtr() noexcept = default;
    WeakPtr(const WeakPtr& otherWeakPtr) noexcept;
    WeakPtr(const SharedPtr<T>& sharedPtr) noexcept;
    WeakPtr(WeakPtr&& otherWeakPtr) noexcept;
    ~WeakPtr();

    size_t use_count() const noexcept;
    bool expired() const noexcept;
    SharedPtr<T> lock() const noexcept;
    void reset() noexcept;

    void handleWeakPtrAndControlBlockDelete();

private:
    T* ptr_ = nullptr;
    SharedControlBlock<T>* controlBlock_ = nullptr;
};

template <typename T>
void WeakPtr<T>::handleWeakPtrAndControlBlockDelete() {
    if (controlBlock_ != nullptr) {
        controlBlock_->decrementWeakRefsCount();
        if (controlBlock_->getSharedRefsCount() == 0 && controlBlock_->getWeakRefsCount() == 0) {
            delete controlBlock_;
        }
    }
}

template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr& otherWeakPtr) noexcept
    : ptr_(otherWeakPtr.ptr_), controlBlock_(otherWeakPtr.controlBlock_) {
    if (controlBlock_ != nullptr) {
        controlBlock_->incrementWeakRefsCount();
    }
}

template <typename T>
WeakPtr<T>::WeakPtr(const SharedPtr<T>& sharedPtr) noexcept
    : ptr_(sharedPtr.ptr_), controlBlock_(sharedPtr.shControlBlock_) {
    if (controlBlock_ != nullptr) {
        controlBlock_->incrementWeakRefsCount();
    }
}

template <typename T>
WeakPtr<T>::WeakPtr(WeakPtr&& otherWeakPtr) noexcept
    : ptr_(std::move(otherWeakPtr.ptr_)), controlBlock_(std::move(otherWeakPtr.controlBlock_)) {}

template <typename T>
WeakPtr<T>::~WeakPtr() {
    handleWeakPtrAndControlBlockDelete();
}

template <typename T>
size_t WeakPtr<T>::use_count() const noexcept {
    if (controlBlock_ != nullptr) {
        return controlBlock_->getSharedRefsCount();
    }
    return 0;
}

template <typename T>
bool WeakPtr<T>::expired() const noexcept {
    return (use_count() == 0);
}

template <typename T>
SharedPtr<T> WeakPtr<T>::lock() const noexcept {
    if (expired()) {
        SharedPtr<T>();
    } else {
        SharedPtr<T>(ptr_);
    }
}

template <typename T>
void WeakPtr<T>::reset() noexcept {
    handleWeakPtrAndControlBlockDelete();
    ptr_ = nullptr;
    controlBlock_ = nullptr;
}
