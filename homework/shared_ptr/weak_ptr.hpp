#pragma once

#include "shared_ptr.hpp"

namespace coders {

template <typename T>
class weak_ptr {
public:
    template <typename Y>
    friend class shared_ptr;

    constexpr weak_ptr() noexcept = default;
    weak_ptr(const shared_ptr<T>& ptr) noexcept;
    weak_ptr(const weak_ptr& ptr) noexcept;
    weak_ptr(weak_ptr&& ptr) noexcept;
    ~weak_ptr();

    weak_ptr<T>& operator=(const shared_ptr<T>& ptr) noexcept;
    weak_ptr<T>& operator=(const weak_ptr<T>& ptr) noexcept;
    weak_ptr<T>& operator=(weak_ptr<T>&& ptr) noexcept;

    void reset() noexcept;
    bool expired() const noexcept;
    shared_ptr<T> lock() const noexcept;
    size_t use_count() const noexcept;

private:
    T* rawPtr_{nullptr};
    control_block<T>* ctrl_{nullptr};

    void deleteStoredPointers();
};

template <typename T>
void weak_ptr<T>::deleteStoredPointers() {
    if (!ctrl_) {
        return;
    }
    ctrl_->decrementWeakRefs();
    if (!ctrl_->getSharedRefs() && !ctrl_->getWeakRefs()) {
        delete ctrl_;
        ctrl_ = nullptr;
    }
}

template <typename T>
weak_ptr<T>::weak_ptr(const shared_ptr<T>& ptr) noexcept
    : rawPtr_(ptr.rawPtr_), ctrl_(ptr.ctrl_) {
    if (ctrl_) {
        ctrl_->incrementWeakRefs();
    }
}

template <typename T>
weak_ptr<T>::weak_ptr(const weak_ptr& ptr) noexcept
    : rawPtr_(ptr.rawPtr_), ctrl_(ptr.ctrl_) {
    if (ctrl_) {
        ctrl_->incrementWeakRefs();
    }
}

template <typename T>
weak_ptr<T>::weak_ptr(weak_ptr&& ptr) noexcept
    : rawPtr_(ptr.rawPtr_), ctrl_(ptr.ctrl_) {
    ptr.rawPtr_ = nullptr;
    ptr.ctrl_ = nullptr;
}

template <typename T>
weak_ptr<T>::~weak_ptr() {
    deleteStoredPointers();
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const shared_ptr<T>& ptr) noexcept {
    deleteStoredPointers();
    rawPtr_ = ptr.rawPtr_;
    ctrl_ = ptr.ctrl_;
    if (ctrl_) {
        ctrl_->incrementWeakRefs();
    }
    return *this;
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr<T>& ptr) noexcept {
    if (this != &ptr) {
        deleteStoredPointers();
        rawPtr_ = ptr.rawPtr_;
        ctrl_ = ptr.ctrl_;
        if (ctrl_) {
            ctrl_->incrementWeakRefs();
        }
    }
    return *this;
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(weak_ptr<T>&& ptr) noexcept {
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
void weak_ptr<T>::reset() noexcept {
    deleteStoredPointers();
    rawPtr_ = nullptr;
    ctrl_ = nullptr;
}

template <typename T>
bool weak_ptr<T>::expired() const noexcept {
    return (!ctrl_ || !ctrl_->getSharedRefs());
}

template <typename T>
shared_ptr<T> weak_ptr<T>::lock() const noexcept {
    return expired() ? coders::shared_ptr<T>() : coders::shared_ptr<T>(*this);
}

template <typename T>
size_t weak_ptr<T>::use_count() const noexcept {
    if (ctrl_) {
        return ctrl_->getSharedRefs();
    }
    return 0;
}

}  // namespace coders
