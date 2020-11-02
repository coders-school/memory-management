#pragma once

#include "control_block.hpp"
#include "exceptions.hpp"

#include <cstddef>
#include <functional>

namespace coders {

template <typename T>
class weak_ptr;

template <typename T>
class shared_ptr {
public:
    template <typename Y>
    friend class weak_ptr;

    shared_ptr(T* ptr = nullptr) noexcept;
    shared_ptr(T* ptr, Deleter<T> deleter) noexcept;
    shared_ptr(const shared_ptr& ptr) noexcept;
    shared_ptr(shared_ptr&& ptr) noexcept;
    explicit shared_ptr(const weak_ptr<T>& wPtr);
    ~shared_ptr();

    shared_ptr<T>& operator=(const shared_ptr<T>& ptr) noexcept;
    shared_ptr<T>& operator=(shared_ptr<T>&& ptr) noexcept;
    T& operator*() const noexcept;
    T* operator->() const noexcept;

    T* get() const noexcept;
    void reset(T* ptr = nullptr, Deleter<T> deleter = defaultDeleter);
    size_t use_count() const noexcept;
    explicit operator bool() const noexcept;

private:
    T* rawPtr_{nullptr};
    control_block<T>* ctrl_{nullptr};

    void deleteStoredPointers();
};

template <typename T>
void shared_ptr<T>::deleteStoredPointers() {
    if (!ctrl_) {
        return;
    }
    ctrl_->decrementSharedRefs();
    if (!ctrl_->getSharedRefs()) {
        ctrl_->getDeleter()(rawPtr_);
        rawPtr_ = nullptr;
        if (!ctrl_->getSharedRefs() && !ctrl_->getWeakRefs()) {
            delete ctrl_;
            ctrl_ = nullptr;
        }
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr) noexcept
    : rawPtr_(ptr) {
    ctrl_ = new control_block<T>();
    ctrl_->incrementSharedRefs();
}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr, Deleter<T> deleter) noexcept
    : rawPtr_(ptr) {
    ctrl_ = new control_block<T>(deleter);
    ctrl_->incrementSharedRefs();
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& ptr) noexcept
    : rawPtr_(ptr.rawPtr_), ctrl_(ptr.ctrl_) {
    ctrl_->incrementSharedRefs();
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& ptr) noexcept
    : rawPtr_(ptr.rawPtr_), ctrl_(ptr.ctrl_) {
    ptr.rawPtr_ = nullptr;
    ptr.ctrl_ = nullptr;
}

template <typename T>
shared_ptr<T>::shared_ptr(const weak_ptr<T>& wPtr) {
    if (wPtr.expired()) {
        throw coders::ExpiredWeakPtr("Expired weak pointer\n");
    }
    rawPtr_ = wPtr.rawPtr_;
    ctrl_ = wPtr.ctrl_;
    ctrl_->incrementSharedRefs();
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    deleteStoredPointers();
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& ptr) noexcept {
    if (this != &ptr) {
        deleteStoredPointers();
        rawPtr_ = ptr.rawPtr_;
        ctrl_ = ptr.ctrl_;
        if (ctrl_) {
            ctrl_->incrementSharedRefs();
        }
    }
    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& ptr) noexcept {
    if (this != &ptr) {
        deleteStoredPointers();
        rawPtr_ = ptr.rawPtr_;
        ctrl_ = ptr.ctrl_;
        ptr.rawPtr_ = nullptr;
        ptr.ctrl_ = nullptr;
    }
    return *this;
}

template <typename T>
T& shared_ptr<T>::operator*() const noexcept {
    return *get();
}

template <typename T>
T* shared_ptr<T>::operator->() const noexcept {
    return get();
}

template <typename T>
T* shared_ptr<T>::get() const noexcept {
    return rawPtr_;
}

template <typename T>
void shared_ptr<T>::reset(T* ptr, Deleter<T> deleter) {
    deleteStoredPointers();
    rawPtr_ = ptr;
    ctrl_ = new control_block<T>(deleter);
    ctrl_->incrementSharedRefs();
}

template <typename T>
size_t shared_ptr<T>::use_count() const noexcept {
    return ctrl_->getSharedRefs();
}

template <typename T>
shared_ptr<T>::operator bool() const noexcept {
    return get() != nullptr;
}

}  // namespace coders
