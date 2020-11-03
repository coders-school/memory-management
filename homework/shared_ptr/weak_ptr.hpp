#pragma once

#include <iostream>

#include "sharedControlBlock.hpp"
#include "shared_ptr.hpp"

namespace cs {

template <typename T>
class shared_ptr;

template <typename T>
class weak_ptr {
public:
    weak_ptr() noexcept = default;
    weak_ptr(const weak_ptr& r) noexcept;
    explicit weak_ptr(const cs::shared_ptr<T>& r) noexcept;
    weak_ptr(weak_ptr&& r) noexcept;

    weak_ptr& operator=(const weak_ptr& r) noexcept;
    weak_ptr& operator=(const shared_ptr<T>& r) noexcept;
    weak_ptr& operator=(weak_ptr&& r) noexcept;
    ~weak_ptr();
    size_t use_count() const noexcept;
    bool expired() const noexcept;
    cs::shared_ptr<T> lock() const noexcept;
    void reset() noexcept;

private:
    T* ptr_ = nullptr;
    SharedControlBlock<T>* controlBlock_ = nullptr;

    void deleteSeq();

    template <typename>
    friend class shared_ptr;
};

template <typename T>
void weak_ptr<T>::deleteSeq() {
    if (controlBlock_) {
        controlBlock_->decrementWeakRefs();
        if (controlBlock_->getSharedRefs() == 0 && controlBlock_->getWeakRefs() == 0) {
            delete controlBlock_;
        }
    }
}

template <typename T>
weak_ptr<T>::weak_ptr(const weak_ptr<T>& r) noexcept
    : ptr_{r.ptr_}, controlBlock_{r.controlBlock_} {
    if (controlBlock_) {
        controlBlock_->incrementWeakRefs();
    }
}

template <typename T>
weak_ptr<T>::weak_ptr(const cs::shared_ptr<T>& r) noexcept
    : ptr_{r.ptr_}, controlBlock_{r.controlBlock_} {
    if (controlBlock_) {
        controlBlock_->incrementWeakRefs();
    }
}

template <typename T>
weak_ptr<T>::weak_ptr(weak_ptr<T>&& r) noexcept
    : ptr_{std::move(r.ptr_)}, controlBlock_{std::move(r.controlBlock_)} {
    r.ptr_ = nullptr;
    r.controlBlock_ = nullptr;
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr<T>& r) noexcept {
    if (this != &r) {
        deleteSeq();

        ptr_ = r.ptr_;
        controlBlock_ = r.controlBlock_;
        if (controlBlock_) {
            controlBlock_->incrementWeakRefs();
        }
    }
    return *this;
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const shared_ptr<T>& r) noexcept {
    if (controlBlock_) {
        deleteSeq();

        ptr_ = r.ptr_;
        controlBlock_ = r.controlBlock_;
        if (controlBlock_) {
            controlBlock_->incrementWeakRefs();
        }
    }
    return *this;
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(weak_ptr<T>&& r) noexcept {
    if (this != &r) {
        deleteSeq();

        ptr_ = r.ptr_;
        controlBlock_ = r.controlBlock_;
        r.ptr_ = nullptr;
        r.controlBlock_ = nullptr;
    }
    return *this;
}

template <typename T>
weak_ptr<T>::~weak_ptr() {
    deleteSeq();
}

template <typename T>
size_t weak_ptr<T>::use_count() const noexcept {
    if (controlBlock_) {
        return controlBlock_->getSharedRefs();
    }
    return 0;
}

template <typename T>
bool weak_ptr<T>::expired() const noexcept {
    return use_count() == 0;
}

template <typename T>
cs::shared_ptr<T> weak_ptr<T>::lock() const noexcept {
    return expired() ? cs::shared_ptr<T>() : cs::shared_ptr<T>(*this);
}

template <typename T>
void weak_ptr<T>::reset() noexcept {
    deleteSeq();

    ptr_ = nullptr;
    controlBlock_ = nullptr;
}

}  // namespace cs
