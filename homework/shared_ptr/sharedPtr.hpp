#pragma once

#include "InvalidDereference.hpp"
#include "sharedControlBlock.hpp"

namespace coders_school {

template <typename T>
class shared_ptr {
public:
    shared_ptr() = default;
    shared_ptr(T* ptr);
    shared_ptr(const shared_ptr& otherPtr);
    shared_ptr(shared_ptr&&);
    ~shared_ptr();

    shared_ptr& operator=(const shared_ptr&);
    shared_ptr& operator=(shared_ptr&&);
    T& operator*() const;
    T* operator->() const;
    operator bool() const;

    T* get() const;
    void reset(T* ptr);
    unsigned int use_count() const;

private:
    T* ptr_{nullptr};
    SharedControlBlock* counter_;
};

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr)
    : ptr_(ptr) {
    counter_ = new SharedControlBlock();
    if (ptr) {
        *(counter_)++;
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& otherPtr) {
    ptr_ = otherPtr.ptr_;
    counter_ = otherPtr.counter_;
    *(counter_)++;
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    *(counter_)--;
    if (counter_->get() == defaultCounterValue) {
        delete counter_;
        delete ptr_;
    }
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
T* shared_ptr<T>::get() const {
    return ptr_;
}

template <typename T>
unsigned int shared_ptr<T>::use_count() const {
    return counter_->get();
}

}  // namespace coders_school