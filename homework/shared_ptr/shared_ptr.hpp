#pragma once

#include <atomic>
#include <functional>
#include "control_block.hpp"
#include "iostream"
#include "weak_ptr.hpp"
namespace cs {
template <typename T>
class weak_ptr;
}  // namespace cs

namespace cs {
template <typename T>
class shared_ptr {
public:
    shared_ptr(T* ptr = nullptr) : ptr_(ptr), cb_(new ControlBlock<T>) {}
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
    void reset(T* ptr = nullptr);

private:
    void deletePointers();

    template <typename Y, typename... Args>
    friend shared_ptr<Y> make_shared(Args&&... args);

    template <typename>
    friend class cs::weak_ptr;

    shared_ptr(BlockAndData<T>* cb) : cb_(cb) { ptr_ = new T{cb->getObject()}; };
    T* ptr_;
    ControlBlock<T>* cb_;
};

template <typename T>
void shared_ptr<T>::deletePointers() {
    if (cb_) {
        cb_->decreaseSharedRef();
        if (cb_->getShared() == 0) {
            cb_->getDeleter()(ptr_);
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
shared_ptr<T>::shared_ptr(const shared_ptr& ptr) : ptr_(ptr.ptr_), cb_(ptr.cb_) {
    cb_->increaseSharedRef();
}

template <typename T>
shared_ptr<T>::shared_ptr(const cs::weak_ptr<T>& ptr) : ptr_(ptr.ptr_), cb_(ptr.cb_) {
    cb_->increaseSharedRef();
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& ptr) : ptr_(ptr.ptr_), cb_(ptr.cb_) {
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
        ptr.ptr_ = nullptr;
        ptr.cb_ = nullptr;
    }
    return *this;
}

template <typename T>
void shared_ptr<T>::reset(T* ptr) {
    deletePointers();
    ptr_ = ptr;
    cb_ = new ControlBlock<T>;
}

template <typename Y, typename... Args>
shared_ptr<Y> make_shared(Args&&... args) {
    return cs::shared_ptr<Y>(new BlockAndData<Y>(std::forward<decltype(args)>(args)...));
}
}  // namespace cs
