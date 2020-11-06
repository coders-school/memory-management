#pragma once

#include "CounterBlock.hpp"
#include "InvalidDereference.hpp"

namespace coders_school {

template <typename T>
class shared_ptr {
public:
    explicit shared_ptr(T* ptr = nullptr);
    shared_ptr(const shared_ptr& otherPtr) noexcept;
    shared_ptr(shared_ptr&& otherPtr) noexcept;
    ~shared_ptr();
    shared_ptr& operator=(const shared_ptr& otherPtr) noexcept;
    shared_ptr& operator=(shared_ptr&& otherPtr) noexcept;
    T& operator*() const;
    T* operator->() const noexcept;
    operator bool() const noexcept;
    T* get() const noexcept;
    unsigned int use_count() noexcept;
    void reset(T* otherPtr = nullptr);

private:
    T* ptr_;
    CounterBlock* counter_;

    void resourcesCleaner();
};

template <typename T>
void shared_ptr<T>::resourcesCleaner() {
    if (ptr_) {
        counter_->decrementCounter();
    }

    if (use_count() == 0) {
        delete counter_;
        counter_ = nullptr;
        delete ptr_;
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr)
    : ptr_(ptr), counter_(new CounterBlock) {
    if (ptr) {
        counter_->incrementCounter();
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& otherPtr) noexcept
    : ptr_(otherPtr.ptr_), counter_(otherPtr.counter_) {
    if (ptr_) {
        counter_->incrementCounter();
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& otherPtr) noexcept
    : ptr_(otherPtr.ptr_), counter_(otherPtr.counter_) {
    otherPtr.ptr_ = nullptr;
    otherPtr.counter_ = nullptr;
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    if (!counter_) {
        return;
    }
    resourcesCleaner();
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& otherPtr) noexcept {
    if (this != &otherPtr && ptr_ != nullptr) {
        resourcesCleaner();
        ptr_ = otherPtr.ptr_;
        counter_ = otherPtr.counter_;
        counter_->incrementCounter();
    }

    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& otherPtr) noexcept {
    if (this != &otherPtr && ptr_ != nullptr) {
        resourcesCleaner();
        ptr_ = otherPtr.ptr_;
        counter_ = otherPtr.counter_;
        otherPtr.ptr_ = nullptr;
        otherPtr.counter_ = nullptr;
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
T* shared_ptr<T>::operator->() const noexcept {
    return ptr_;
}

template <typename T>
shared_ptr<T>::operator bool() const noexcept {
    return ptr_ != nullptr;
}

template <typename T>
T* shared_ptr<T>::get() const noexcept {
    return ptr_;
}

template <typename T>
unsigned int shared_ptr<T>::use_count() noexcept {
    return counter_->getCounter();
}

template <typename T>
void shared_ptr<T>::reset(T* otherPtr) {
    delete ptr_;
    counter_->resetCounter();
    ptr_ = otherPtr;
}

}  // namespace coders_school