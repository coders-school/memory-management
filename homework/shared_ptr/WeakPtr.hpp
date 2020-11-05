#pragma once

#include "SharedControlBlock.hpp"
#include "SharedPtr.hpp"

namespace cs {
template <typename T>
class SharedPtr;

template <typename T>
class WeakPtr {
public:
    constexpr WeakPtr() noexcept = default;
    ~WeakPtr();

    WeakPtr(const WeakPtr& otherWeakPtr) noexcept;
    WeakPtr(const cs::SharedPtr<T>& sharedPtr) noexcept;
    WeakPtr(WeakPtr&& otherWeakPtr) noexcept;

    WeakPtr& operator=(const WeakPtr& otherWeakPtr) noexcept;
    WeakPtr& operator=(const cs::SharedPtr<T>& sharedPtr) noexcept;
    WeakPtr& operator=(WeakPtr&& otherWeakPtr) noexcept;

    size_t use_count() const noexcept;
    bool expired() const noexcept;
    cs::SharedPtr<T> lock() const noexcept;
    void reset() noexcept;

private:
    T* ptr_ = nullptr;
    SharedControlBlock<T>* controlBlock_ = nullptr;

    void handleWeakPtrAndControlBlockDelete();

    template <typename>
    friend class cs::SharedPtr;
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
WeakPtr<T>::~WeakPtr() {
    handleWeakPtrAndControlBlockDelete();
}

template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr& otherWeakPtr) noexcept
    : ptr_(otherWeakPtr.ptr_), controlBlock_(otherWeakPtr.controlBlock_) {
    if (controlBlock_ != nullptr) {
        controlBlock_->incrementWeakRefsCount();
    }
}

template <typename T>
WeakPtr<T>::WeakPtr(const cs::SharedPtr<T>& sharedPtr) noexcept
    : ptr_(sharedPtr.ptr_), controlBlock_(sharedPtr.shControlBlock_) {
    if (controlBlock_ != nullptr) {
        controlBlock_->incrementWeakRefsCount();
    }
}

template <typename T>
WeakPtr<T>::WeakPtr(WeakPtr&& otherWeakPtr) noexcept
    : ptr_(std::move(otherWeakPtr.ptr_)), controlBlock_(std::move(otherWeakPtr.controlBlock_)) {
    otherWeakPtr.ptr_ = nullptr;
    otherWeakPtr.controlBlock_ = nullptr;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr& otherWeakPtr) noexcept {
    if (&otherWeakPtr != this) {
        handleWeakPtrAndControlBlockDelete();

        ptr_ = otherWeakPtr.ptr_;
        controlBlock_ = otherWeakPtr.controlBlock_;
        if (controlBlock_ != nullptr) {
            controlBlock_->incrementWeakRefsCount();
        }
    }
    return *this;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const cs::SharedPtr<T>& sharedPtr) noexcept {
    handleWeakPtrAndControlBlockDelete();

    ptr_ = sharedPtr.ptr_;
    controlBlock_ = sharedPtr.shControlBlock_;
    if (controlBlock_ != nullptr) {
        controlBlock_->incrementWeakRefsCount();
    }
    return *this;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr&& otherWeakPtr) noexcept {
    if (&otherWeakPtr != this) {
        handleWeakPtrAndControlBlockDelete();
        ptr_ = otherWeakPtr.ptr_;
        controlBlock_ = otherWeakPtr.controlBlock_;
        otherWeakPtr.ptr_ = nullptr;
        otherWeakPtr.controlBlock_ = nullptr;
    }
    return *this;
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
cs::SharedPtr<T> WeakPtr<T>::lock() const noexcept {
    if (expired()) {
        return cs::SharedPtr<T>();
    } else {
        return cs::SharedPtr<T>(*this);
    }
}

template <typename T>
void WeakPtr<T>::reset() noexcept {
    handleWeakPtrAndControlBlockDelete();
    ptr_ = nullptr;
    controlBlock_ = nullptr;
}
}  // namespace cs
