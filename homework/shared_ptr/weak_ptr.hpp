#pragma once

#include "control_block.hpp"
#include "shared_ptr.hpp"

namespace cs {
template <typename T>
class weak_ptr {
public:
    constexpr weak_ptr() noexcept
        : ptr_{}, counter_{} {}
    weak_ptr(const weak_ptr& ptr) noexcept;
    weak_ptr(const shared_ptr<T>& ptr) noexcept;
    weak_ptr(weak_ptr<T>&& previousOwner) noexcept;
    ~weak_ptr();

    weak_ptr& operator=(const weak_ptr<T>& ptr) noexcept;
    // weak_ptr& operator=(const shared_ptr<T>& ptr) noexcept;
    weak_ptr& operator=(weak_ptr<T>&& previousOwner) noexcept;

    // void reset() noexcept;
    // long use_count() const noexcept;
    // bool expired() const noexcept;
    shared_ptr<T> lock() const noexcept;

private:
    control_block* counter_{nullptr};
    T* ptr_{nullptr};
};

template <typename T>
weak_ptr<T>::weak_ptr(const weak_ptr& ptr) noexcept
    : ptr_(ptr.ptr_), counter_(ptr.counter_) {
    if (ptr_) {
        counter_->increaseWeakRefs();
    }
}

template <typename T>
shared_ptr<T> weak_ptr<T>::lock() const noexcept {
    return cs::shared_ptr<T>(ptr_, counter_);
}

template <typename T>
weak_ptr<T>::weak_ptr(const shared_ptr<T>& sPtr) noexcept
    : ptr_{sPtr.ptr_}, counter_{sPtr.counter_} {  //TODO implement
    if (counter_) {
        counter_->increaseWeakRefs();
    }
}

template <typename T>
weak_ptr<T>::weak_ptr(weak_ptr<T>&& previousOwner) noexcept
    : ptr_(previousOwner.ptr_), counter_(previousOwner.counter_) {
    previousOwner.ptr_ = nullptr;
    previousOwner.counter_ = nullptr;
}

template <typename T>
weak_ptr<T>::~weak_ptr() {
    if (counter_ != nullptr) {
        if (!counter_->getWeakRefs() && !counter_->getRefs()) {
            delete counter_;
        } else {
            counter_->decreaseWeakRefs();
        }
    }
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr<T>& ptr) noexcept {
    if (counter_) {
        counter_->decreaseWeakRefs();
    }
    //checkAndDeletePointers();
    counter_ = ptr.counter_;
    ptr_ = ptr.ptr_;
    counter_->increaseWeakRefs();

    return *this;
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(weak_ptr<T>&& previousOwner) noexcept {
    if (this != &previousOwner) {
        counter_->decreaseWeakRefs();
        //checkAndDeletePointers();
        ptr_ = previousOwner.ptr_;
        counter_ = previousOwner.counter_;
        previousOwner.ptr_ = nullptr;
        previousOwner.counter_ = nullptr;
    }
    return *this;
}

} //namespace cs