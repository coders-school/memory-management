#pragma once

#include <atomic>
#include <functional>
#include "weak_ptr.hpp"
#include "control_block.hpp"

namespace cs {
template <typename T>
class shared_ptr {
public:
    shared_ptr(T* ptr = nullptr)
        : ptr_(ptr), cb_(new ControlBlock([&]() { delete ptr_; })) {}
    shared_ptr(const shared_ptr& ptr);
    shared_ptr(const cs::weak_ptr<T>& ptr);
    shared_ptr(shared_ptr&& ptr);
    shared_ptr& operator=(const shared_ptr& ptr);
    shared_ptr& operator=(shared_ptr&& ptr);
    ~shared_ptr();
    T* get() const { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    long use_count() const { return static_cast<long>(cb_->getShared()); }
    explicit operator bool() const { return ptr_ != nullptr; }
    void reset(T* ptr);

private:
    void deletePointers();
    T* ptr_;
    ControlBlock* cb_;
};

template <typename T>
void shared_ptr<T>::deletePointers() {
    if (cb_) {
        cb_->decreaseSharedRef();
        if (cb_->getShared() == 0) {
            cb_->callDeleter();
            if (cb_->getWeak() == 0) {
                delete cb_;
            }
        }
    }
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    deletePointers();
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& ptr) {
    ptr_ = ptr.ptr_;
    cb_ = ptr.cb_;
    cb_->increaseSharedRef();
}

template <typename T>
shared_ptr<T>::shared_ptr(const cs::weak_ptr<T>& ptr) {
    ptr_ = ptr.ptr_;
    cb_ = ptr.cb_;
    cb_->increaseSharedRef();
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& ptr) {
    ptr_ = ptr.ptr_;
    cb_ = ptr.cb_;
    cb_->setDeleter([&]() { delete ptr_; });
    ptr.ptr_ = nullptr;
    ptr.cb_ = nullptr;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& ptr) {
    if (&ptr != this) {
        deletePointers(); 
        ptr_ = ptr.ptr_;
        cb_ = ptr.cb_;
        cb_->increaseSharedRef();
    }
    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& ptr) {
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
void shared_ptr<T>::reset(T* ptr) {
    *ptr_ = *ptr;
    delete ptr;
}
}  // namespace cs
