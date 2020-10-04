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

private:
    T* ptr_ = nullptr;
    SharedControlBlock<T>* controlBlock_ = nullptr;
};
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
    if (controlBlock_ != nullptr) {
        controlBlock_->decrementWeakRefsCount();
        if (controlBlock_->getSharedRefsCount() == 0 && controlBlock_->getWeakRefsCount() == 0) {
            delete controlBlock_;
        }
    }
}

// * Member functions: `use_count()`, `expired()`, `lock()`, `reset()`
