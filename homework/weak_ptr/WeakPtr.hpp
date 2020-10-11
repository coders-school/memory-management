#pragma once
#include <algorithm>
#include "../shared_ptr/SharedPtr.hpp"

template <typename T> class WeakPtr {
public:
    constexpr WeakPtr() noexcept = default;
    WeakPtr(const WeakPtr<T> & otherPtr) noexcept;
    WeakPtr(const SharedPtr<T> & otherPtr) noexcept;
    WeakPtr(WeakPtr && otherPtr) noexcept;
    ~WeakPtr();

    WeakPtr & operator=(const WeakPtr & otherPtr) noexcept;
    WeakPtr & operator=(const SharedPtr<T> & otherPtr) noexcept;
    WeakPtr & operator=(WeakPtr && otherPtr) noexcept;

    size_t useCount() const noexcept;
    size_t useSCount() const noexcept;
    bool expired() const noexcept;
    SharedPtr<T> lock() const noexcept;
    void reset() noexcept;
    void controlBlockRemover();
    void weakCounterDecrementer();
    void weakCounterIncrementer();

private:
    T * rawPtr_;
    ControlBlock<T> * ControlBlock_;
};

template <typename T>
void WeakPtr<T>::controlBlockRemover() {
    if (ControlBlock_->sharedRefsCounter_ == 0 && ControlBlock_->weakRefsCounter_ == 0) {
        delete ControlBlock_;
    }
}

template <typename T>
void WeakPtr<T>::weakCounterDecrementer() {
    ControlBlock_->weakRefsCounter_.exchange(ControlBlock_->weakRefsCounter_.load(std::memory_order_relaxed) - 1,
    std::memory_order_relaxed);
}

template <typename T>
void WeakPtr<T>::weakCounterIncrementer() {
    ControlBlock_->weakRefsCounter_.exchange(ControlBlock_->weakRefsCounter_.load(std::memory_order_relaxed) + 1,
    std::memory_order_relaxed);
}

template <typename T>
WeakPtr<T>::WeakPtr(const SharedPtr<T> & otherPtr) noexcept
    : rawPtr_(otherPtr.getPtr()), ControlBlock_(otherPtr.getControlBlock()) {
      weakCounterIncrementer();
}

template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr<T> & otherPtr) noexcept
    : rawPtr_(otherPtr.rawPtr_), ControlBlock_(otherPtr.ControlBlock_) {
      weakCounterIncrementer();
}

template <typename T>
WeakPtr<T>::WeakPtr(WeakPtr<T> && otherPtr) noexcept
    : rawPtr_(otherPtr.getPtr()), ControlBlock_(otherPtr.getControlBlock()) {
      otherPtr.rawPtr_ = nullptr;
      otherPtr.ControlBlock_ = nullptr;
}

template <typename T>
WeakPtr<T>::~WeakPtr() {
    if (ControlBlock_) {
        weakCounterDecrementer();
        controlBlockRemover();
    }
}

template <typename T> 
WeakPtr<T> & WeakPtr<T>::operator=(const WeakPtr & otherPtr) noexcept {
    if (this != & otherPtr) {
        rawPtr_ = otherPtr.rawPtr_;
        ControlBlock_ = otherPtr.ControlBlock_;
        weakCounterIncrementer();
    }
    return *this;
}

template <typename T> 
WeakPtr<T> & WeakPtr<T>::operator=(const SharedPtr<T> & otherPtr) noexcept {
    if (ControlBlock_) {
        rawPtr_ = otherPtr.rawPtr_;
        ControlBlock_ = otherPtr.ControlBlock_;
        weakCounterIncrementer();
    }
    return *this;
}

template <typename T> 
WeakPtr<T> & WeakPtr<T>::operator=(WeakPtr && otherPtr) noexcept {
    if (this != otherPtr) {
        rawPtr_ = otherPtr.rawPtr_;
        ControlBlock_ = otherPtr.ControlBlock_;
        otherPtr.rawPtr_ = nullptr;
        otherPtr.ControlBlock_ = nullptr;
    }
    return *this;
}

template <typename T>
size_t WeakPtr<T>::useCount() const noexcept {
    return ControlBlock_->weakRefsCounter_;
}

template <typename T>
size_t WeakPtr<T>::useSCount() const noexcept {
    return ControlBlock_->sharedRefsCounter_;
}

template <typename T>
bool WeakPtr<T>::expired() const noexcept {
    return useCount() == 0;
}

template <typename T>
SharedPtr<T> WeakPtr<T>::lock() const noexcept {
    if (expired()) {
        return SharedPtr<T>();
    }
    return SharedPtr<T>(*this);
}

template <typename T>
void WeakPtr<T>::reset() noexcept {
    rawPtr_ = nullptr;
    if (ControlBlock_) {
        weakCounterDecrementer();
        controlBlockRemover();
    } else {
        ControlBlock_ = nullptr;
    }
}
