#pragma once

#include "control_block.hpp"

#include <algorithm> //for swap method
#include <stdexcept>

namespace cs {
    
template <typename T>
class weak_ptr;

template <typename T>
class shared_ptr {
public:
    template <typename B> friend class weak_ptr;
    shared_ptr(T* ptr = nullptr);
    shared_ptr(const shared_ptr& ptr) noexcept;  //copy c-tor
    shared_ptr(shared_ptr&& previousOwner) noexcept;      //move c-tor
    ~shared_ptr();

    //TODO Implement swap
    void swap(shared_ptr<T>& secondPointer) noexcept;
    const T* get() const;
    void reset(T* newPtr = nullptr);

    const T* operator->();
    T& operator*();
    explicit operator bool() const noexcept;
    shared_ptr<T>& operator=(const shared_ptr<T>& ptr) noexcept;             //copy assignment
    shared_ptr<T>& operator=(shared_ptr<T>&& previousOwner);  //move assignment

    size_t use_count() { return counter_->getRefs(); }

private:
    shared_ptr(T* ptr, control_block* counter);
    control_block* counter_{nullptr};
    T* ptr_{nullptr};

    void checkAndDeletePointers();
};

template <typename T>
void shared_ptr<T>::checkAndDeletePointers() {
    if (!counter_->getRefs()) {
        delete ptr_;
        if (!counter_->getWeakRefs()) {
            delete counter_;
        }
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr, control_block* counter) : ptr_(ptr), counter_(counter) {
    ++*counter_;
}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr)
    : ptr_(ptr) {
    if (ptr_) {
        counter_ = new control_block();
        ++(*counter_);
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& ptr) noexcept
    : counter_(ptr.counter_), ptr_(ptr.ptr_) {
    ++(*counter_);
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& previousOwner) noexcept
    :   ptr_(previousOwner.ptr_), counter_(previousOwner.counter_) {
    previousOwner.ptr_ = nullptr;
    previousOwner.counter_ = nullptr;
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    if (counter_ != nullptr) {
        --*counter_;
        checkAndDeletePointers();
    }
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr<T>& secondPointer) noexcept {
    auto ptrTmp = secondPointer.ptr_;
    auto counterTmp = secondPointer.counter_;
    secondPointer.ptr_ = ptr_;
    secondPointer.counter_ = counter_;
    ptr_ = ptrTmp;
    counter_ = counterTmp;
}

template <typename T>
const T* shared_ptr<T>::get() const {
    return ptr_;
}

template <typename T>
void shared_ptr<T>::reset(T* newPtr) {
    shared_ptr{newPtr}.swap(*this);
}

template <typename T>
const T* shared_ptr<T>::operator->() {
    return ptr_;
}

template <typename T>
T& shared_ptr<T>::operator*() {
    if(!ptr_) {
        throw std::runtime_error("Dereferencing a nullptr");
    }
    return *ptr_;
}

template <typename T>
shared_ptr<T>::operator bool() const noexcept {
    return ptr_;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& previousOwner) {
    if (this != &previousOwner) {
        --*counter_;
        checkAndDeletePointers();

        ptr_ = previousOwner.ptr_;
        counter_ = previousOwner.counter_;
        previousOwner.ptr_ = nullptr;
        previousOwner.counter_ = nullptr;
    }

    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& ptr) noexcept {
    --*counter_;
    checkAndDeletePointers();
    counter_ = ptr.counter_;
    ptr_ = ptr.ptr_;
    ++(*counter_);
}

}  // namespace cs
