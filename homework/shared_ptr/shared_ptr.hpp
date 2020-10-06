#pragma once

#include "control_block.hpp"

#include <stdexcept>
#include <iostream>
namespace cs {
    
template <typename T>
class weak_ptr;

template <typename T>
class shared_ptr {
public:
    template <typename B> friend class weak_ptr;
    template <typename C> friend shared_ptr<C>make_shared(const C& object);
    template<typename D, typename... Args> friend shared_ptr<D> make_shared(Args&& ... args);
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
    shared_ptr(const T& object);
    shared_ptr(T* ptr, control_block<T>* counter);
    control_block<T>* counter_{nullptr};
    T* ptr_{nullptr};

    void checkAndDeletePointers();
};

template <typename T>
void shared_ptr<T>::checkAndDeletePointers() {
    if (!counter_->getRefs()) {
        if(typeid(*counter_) == typeid(control_block<T>)) {
            delete ptr_;
        }
        if (!counter_->getWeakRefs()) {
            delete counter_;
        }
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr, control_block<T>* counter) : ptr_(ptr), counter_(counter) {
    ++*counter_;
}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr)
    : ptr_(ptr) {
    if (ptr_) {
        counter_ = new control_block<T>();
        ++(*counter_);
    }
}

template<typename T>
shared_ptr<T>::shared_ptr(const T& object) {
    counter_ = new continuous_block<T>(object);
    ptr_ = counter_->getObjectPointer();
    ++(*counter_);
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
    if (counter_->getRefs() == 1) {
        delete ptr_;
    }
    else {
        counter_ = new control_block<T>();
        ++(*counter_);
    }
    ptr_ = newPtr;
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

template<typename C>
shared_ptr<C> make_shared(const C &object) {
    return shared_ptr<C>(object);
}

template<typename D, typename... Args>
shared_ptr<D> make_shared(Args&&... args) {
    auto tempCounter = new continuous_block<D>(args...);
    return shared_ptr<D>(tempCounter->getObjectPointer(), tempCounter);
}

}  // namespace cs
