#pragma once

#include "control_block.hpp"

#include <cstddef>

namespace coders {

template <typename T>
class shared_ptr {
public:
    shared_ptr(T* ptr = nullptr) noexcept;
    shared_ptr(const shared_ptr<T>&) noexcept;
    shared_ptr(shared_ptr<T>&& ptr) noexcept;
    ~shared_ptr();

    T* get() const noexcept;
    size_t use_count() const noexcept;
    explicit operator bool() const noexcept;
    void reset(T* ptr = nullptr);

    shared_ptr<T>& operator=(const shared_ptr<T>& ptr) noexcept;
    // shared_ptr<T>& operator=(shared_ptr<T>&& ptr) noexcept;
    T& operator*() const noexcept;
    T* operator->() const noexcept;

    void setDeleter(void (*del)(void*)) { ctrl_->deleter_ = del; }

private:
    T* rawPtr_{nullptr};
    control_block<T>* ctrl_{nullptr};
};

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr) noexcept {
    rawPtr_ = ptr;
    ctrl_ = new control_block<T>();
    ctrl_->incrementSharedRefs();
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>&) noexcept {
    ctrl_->incrementSharedRefs();
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T>&& ptr) noexcept {
    rawPtr_ = ptr.rawPtr_;
    ptr.rawPtr_ = nullptr;
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    ctrl_->decrementSharedRefs();
    if (!ctrl_->getSharedRefs()) {
        if (ctrl_->deleter_) {
            ctrl_->deleter_(rawPtr_);
        } else {
            delete rawPtr_;
        }
    }
    if (!ctrl_->getSharedRefs() && !ctrl_->getWeakRefs()) {
        delete ctrl_;
    }
}

template <typename T>
T* shared_ptr<T>::get() const noexcept {
    return rawPtr_;
}

template <typename T>
size_t shared_ptr<T>::use_count() const noexcept {
    return ctrl_->getSharedRefs();
}

template <typename T>
shared_ptr<T>::operator bool() const noexcept {
    return get() != nullptr;
}

template <typename T>
void shared_ptr<T>::reset(T* ptr) {
    delete rawPtr_;
    rawPtr_ = ptr;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& ptr) noexcept {
    if (this != &ptr) {
        ctrl_->incrementSharedRefs();
    }
    return *this;
}

// template <typename T>
// shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& ptr) noexcept {
//     if (this != &ptr) {
//         delete rawPtr_;
//         rawPtr_ = ptr.rawPtr_;
//         ptr.rawPtr_ = nullptr;
//     }
//     return *this;
// }

template <typename T>
T& shared_ptr<T>::operator*() const noexcept {
    return *get();
}

template <typename T>
T* shared_ptr<T>::operator->() const noexcept {
    return get();
}

}  // namespace coders
