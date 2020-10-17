#pragma once

#include <memory>
#include "control_block.hpp"
#include "shared_ptr.hpp"
namespace cs {
template <typename T>
class shared_ptr;
}  // namespace cs

namespace cs {
template <typename T>
class weak_ptr {
public:
    weak_ptr() = default;
    weak_ptr(const weak_ptr& ptr) noexcept;
    weak_ptr(const cs::shared_ptr<T>& ptr) noexcept;
    weak_ptr(weak_ptr&& ptr) noexcept;
    weak_ptr& operator=(const weak_ptr& ptr) noexcept;
    weak_ptr& operator=(const cs::shared_ptr<T>& ptr) noexcept;
    weak_ptr& operator=(weak_ptr&& ptr) noexcept;
    long use_count() const { return static_cast<long>(cb_->getShared()); }
    bool expired() const noexcept {
        return use_count() == 0;
    }  // musi byc lepszy sposob...
    cs::shared_ptr<T> lock() const noexcept;
    void reset() noexcept;
    ~weak_ptr();

private:
    T* ptr_;
    ControlBlock* cb_;
    void deletePointers();

    template <typename>
    friend class shared_ptr;
};

template <typename T>
void weak_ptr<T>::deletePointers() {
    if (cb_) {
        cb_->decreaseWeakRef();
        if (cb_->getShared() == 0 && cb_->getWeak() == 0) {
            delete cb_;
        }
    }
}

template <typename T>
weak_ptr<T>::~weak_ptr() {
    deletePointers();
}

template <typename T>
weak_ptr<T>::weak_ptr(const weak_ptr& ptr) noexcept {
    if (this != &ptr) {
        ptr_ = ptr.ptr_;
        cb_ = ptr.cb_;
        cb_->increaseWeakRef();
    }
}

template <typename T>
weak_ptr<T>::weak_ptr(const cs::shared_ptr<T>& ptr) noexcept {
    ptr_ = ptr.ptr_;
    cb_ = ptr.cb_;
    cb_->increaseWeakRef();
}

template <typename T>
weak_ptr<T>::weak_ptr(weak_ptr&& ptr) noexcept {
    if (this != &ptr) {
        ptr_ = ptr.ptr_;
        cb_ = ptr.cb_;
        cb_->setDeleter([&]() { delete ptr_; });
        ptr.ptr_ = nullptr;
        ptr.cb_ = nullptr;
    }
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr& ptr) noexcept {
    if (&ptr != this) {
        ptr_ = ptr.ptr_;
        cb_ = ptr.cb_;
        cb_->increaseWeakRef();
    }
    return *this;
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(weak_ptr&& ptr) noexcept {
    if (&ptr != this) {
        deletePointers();
        ptr_ = ptr.ptr_;
        cb_ = ptr.cb_;
        cb_->setDeleter([&]() { delete ptr_; });
        ptr.ptr_ = nullptr;
        ptr.cb_ = nullptr;
    }
    return *this;
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const cs::shared_ptr<T>& ptr) noexcept {
    ptr_ = ptr.ptr_;
    cb_ = ptr.cb_;
    cb_->increaseWeakRef();

    return *this;
}

template <typename T>
cs::shared_ptr<T> weak_ptr<T>::lock() const noexcept {
    return expired() ? cs::shared_ptr<T>() : cs::shared_ptr<T>(*this);
}

template <typename T>
void weak_ptr<T>::reset() noexcept {
    cb_->decreaseWeakRef();
    deletePointers();
    ptr_ = nullptr;
    cb_ = nullptr;
}
}  // namespace cs
