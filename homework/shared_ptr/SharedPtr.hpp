#pragma once

#include "InvalidDereference.hpp"
#include "ReferenceCounterBlock.hpp"

namespace coders_school {

template <typename T>
class shared_ptr {
public:
    shared_ptr() = default;
    shared_ptr(T* ptr);
    shared_ptr(const shared_ptr& otherPtr);
    shared_ptr(shared_ptr&& otherPtr);
    ~shared_ptr();
    shared_ptr& operator=(const shared_ptr& otherPtr);
    shared_ptr& operator=(shared_ptr&& otherPtr);
    T& operator*() const;
    T* operator->() const;
    operator bool() const;
    T* get() const;
    unsigned int use_count();
    void reset(T* ptr);

private:
    T* ptr_{nullptr};
    ReferenceCounterBlock* counter_{};

    void deleter();
};

template <typename T>
void shared_ptr<T>::deleter() {
    counter_->operator--();
    if (use_count() == 0) {
        delete ptr_;
        delete counter_;
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr)
    : ptr_(ptr), counter_(new ReferenceCounterBlock) {
    if (ptr) {
        counter_->operator++();
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& otherPtr) {
    ptr_ = otherPtr.ptr_;
    counter_ = otherPtr.counter_;
    if (ptr_) {
        counter_->operator++();
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& otherPtr) {
    ptr_ = otherPtr.ptr_;
    counter_ = otherPtr.counter_;
    otherPtr.ptr_ = otherPtr.counter_ = nullptr;
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    deleter();
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& otherPtr) {
    if (this != &otherPtr && ptr_ != nullptr) {
        deleter();
        ptr_ = otherPtr.ptr_;
        counter_ = otherPtr.counter_;
        counter_->operator++();
    }

    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& otherPtr) {
    if (this != &otherPtr && ptr_ != nullptr) {
        deleter();
        ptr_ = otherPtr.ptr_;
        counter_ = otherPtr.counter_;
        otherPtr.ptr_ = otherPtr.counter_ = nullptr;
    }

    return *this;
}

template <typename T>
T& shared_ptr<T>::operator*() const {
    if (!ptr_) {
        throw InvalidDereference("You can not derefernce a nullptr!");
    }

    return *ptr_;
}

template <typename T>
T* shared_ptr<T>::operator->() const {
    return ptr_;
}

template <typename T>
shared_ptr<T>::operator bool() const {
    if (!ptr_) {
        return false;
    }

    return true;
}

template <typename T>
T* shared_ptr<T>::get() const {
    return ptr_;
}

template <typename T>
unsigned int shared_ptr<T>::use_count() {
    return counter_->getCounter();
}

template <typename T>
void shared_ptr<T>::reset(T* ptr) {
    if (ptr_) {
        deleter();
    }
    ptr_ = ptr;
    delete ptr;
}

}  // namespace coders_school