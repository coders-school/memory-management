#pragma once

#include <iostream>
#include "ControlBlock.hpp"
#include "SharedPtr.hpp"

namespace cs {
template <typename T>
class SharedPtr;
}  // namespace cs

namespace cs {
template <typename T>
class WeakPtr {
public:
    WeakPtr() noexcept = default;
    WeakPtr(const WeakPtr& ptr) noexcept;
    WeakPtr(const cs::SharedPtr<T>& ptr) noexcept;
    WeakPtr(WeakPtr&& ptr) noexcept;
    ~WeakPtr();

    WeakPtr& operator=(const WeakPtr& ptr) noexcept;
    WeakPtr& operator=(const cs::SharedPtr<T>& ptr) noexcept;
    WeakPtr& operator=(WeakPtr&& ptr) noexcept;

    long useCount() const noexcept; 
    bool expired() const noexcept { return useCount() == 0; }
    void reset() noexcept;
    cs::SharedPtr<T> lock() const noexcept;

private:
    template <typename>
    friend class SharedPtr;

    void deleteResources();

    T* ptr_ = nullptr;
    ControlBlockData<T>* cb_ = nullptr;
};

template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr& ptr) noexcept {
    if (this != &ptr) {
        ptr_ = ptr.ptr_;
        cb_ = ptr.cb_;
        cb_->increaseWeakRefCounter();
    }
}

template <typename T>
WeakPtr<T>::WeakPtr(WeakPtr&& ptr) noexcept {
    if (this != &ptr) {
        ptr_ = ptr.ptr_;
        cb_ = ptr.cb_;
        ptr.ptr_ = nullptr;
        ptr.cb_ = nullptr;
    }
}

template <typename T>
WeakPtr<T>::WeakPtr(const cs::SharedPtr<T>& ptr) noexcept {
    ptr_ = ptr.ptr_;
    cb_ = ptr.cb_;
    cb_->increaseWeakRefCounter();
}

template <typename T>
WeakPtr<T>::~WeakPtr() {
    deleteResources();
}

template <typename T>
void WeakPtr<T>::deleteResources() {
    if (cb_) {
        cb_->decreaseWeakRefCounter();
        if (cb_->getSharedCounter() == 0 && cb_->getWeakCounter() == 0) {
            delete cb_;
        }
    }
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr& ptr) noexcept {
    if (&ptr != this) {
        deleteResources();
        ptr_ = ptr.ptr_;
        cb_ = ptr.cb_;
        cb_->increaseWeakRefCounter();
    }
    return *this;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr&& ptr) noexcept {
    if (&ptr != this) {
        deleteResources();
        ptr_ = ptr.ptr_;
        cb_ = ptr.cb_;
        ptr.ptr_ = nullptr;
        ptr.cb_ = nullptr;
    }
    return *this;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const cs::SharedPtr<T>& ptr) noexcept {
    ptr_ = ptr.ptr_;
    cb_ = ptr.cb_;
    cb_->increaseWeakRefCounter();

    return *this;
}

template <typename T>
cs::SharedPtr<T> WeakPtr<T>::lock() const noexcept {
    return expired() ? cs::SharedPtr<T>() : cs::SharedPtr<T>(*this);
}

template <typename T>
void WeakPtr<T>::reset() noexcept {
    deleteResources();
    ptr_ = nullptr;
    cb_ = nullptr;
}

template <typename T>
long WeakPtr<T>::useCount() const noexcept {
    if (cb_) {
        return cb_->getSharedCounter();
    }
    return 0l;
}
}  // namespace cs