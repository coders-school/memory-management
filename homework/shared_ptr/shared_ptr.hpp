#pragma once

#include "control_block.hpp"

//#include <algorithm> //for swap method

namespace cs {
template <typename T>
class shared_ptr {
public:
    shared_ptr(T* ptr);
    shared_ptr(const shared_ptr& ptr) noexcept;  //copy c-tor
    shared_ptr(shared_ptr&& previousOwner) noexcept;      //move c-tor
    ~shared_ptr();

    //TODO Implement swap
    const T* get() const;
    void reset(T* newPtr = nullptr);
    //void swap(T& otherPtr) noexcept;

    const T* operator->();
    T& operator*();
    explicit operator bool() const noexcept;
    shared_ptr<T>& operator=(const shared_ptr<T>& ptr) noexcept;             //copy assignment
    shared_ptr<T>& operator=(shared_ptr<T>&& previousOwner);  //move assignment

    size_t getRefs() { return counter_->getRefs(); } // for test purpose

private:
    control_block* counter_{nullptr};
    T* ptr_{nullptr};
};

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr)
    : ptr_(ptr), counter_(new control_block()) {
    if (ptr_) {
        counter_->incrementRefs();
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& ptr) noexcept
    : counter_(ptr.counter_), ptr_(ptr.ptr_) {
    counter_->incrementRefs();
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
        counter_->decrementRefs();
        if ((counter_->getRefs()) == 0) {
            delete ptr_;
            delete counter_;
        }
    } 
}

template <typename T>
const T* shared_ptr<T>::get() const {
    return ptr_;
}

template <typename T>
void shared_ptr<T>::reset(T* newPtr) {
    delete ptr_;
    ptr_ = newPtr;
}

// TODO SWAP
// template <typename T>
// void shared_ptr<T>::swap(T& otherValue) noexcept {
//     std::swap(ptr_, otherValue.ptr_);
//     //counter_.swap()
// }

template <typename T>
const T* shared_ptr<T>::operator->() {
    return ptr_;
}

template <typename T>
T& shared_ptr<T>::operator*() {
    return *ptr_;
}

template <typename T>
shared_ptr<T>::operator bool() const noexcept {
    return ptr_;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& previousOwner) {
    if (this != &previousOwner) {
        delete ptr_;
        // delete counter_;
        ptr_ = previousOwner.ptr_;
        // counter_ = previousOwner.counter_;
        previousOwner.ptr_ = nullptr;
        // previousOwner.counter_ = nullptr;
    }

    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& ptr) noexcept {
    //TODO check for memory leak
    // counter_ = ptr.counter_;
    ptr_ = ptr.ptr_;
    // *counter_++;
}

}  // namespace cs
