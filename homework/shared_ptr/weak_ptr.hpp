#pragma once
#include <atomic>
#include "shared_ptr.hpp"

namespace my {

template <typename T>
class weak_ptr {
    friend class shared_ptr<T>;

public:
    weak_ptr() noexcept;
    weak_ptr(const shared_ptr<T>& other) noexcept;
    weak_ptr(const weak_ptr<T>& other) noexcept;

    ~weak_ptr() noexcept;

    int use_count() const noexcept;
    bool expired() const noexcept;
    shared_ptr<T> lock() const noexcept;
    void reset() noexcept;

private:
    T* ptr_;
    controlBlock* ptrToControlBlock_;
};

template <typename T>
weak_ptr<T>::weak_ptr() noexcept
    : ptr_(nullptr), ptrToControlBlock_(nullptr) {
}

template <typename T>
weak_ptr<T>::weak_ptr(const shared_ptr<T>& other) noexcept {
    ptr_ = other.get();
    ptrToControlBlock_ = other.getControlBlockPtr();
    if (ptr_) {
        ptrToControlBlock_->incrementWeakRefs();
    }
}

template <typename T>
weak_ptr<T>::weak_ptr(const weak_ptr<T>& other) noexcept {
    ptr_ = other.ptr_;
    ptrToControlBlock_ = other.ptrToControlBlock_;
    if (ptr_ != nullptr) {
        ptrToControlBlock_->incrementWeakRefs();
    }
}

template <typename T>
weak_ptr<T>::~weak_ptr() noexcept {
    if (ptrToControlBlock_) {
        ptrToControlBlock_->decrementWeakRefs();
        if (ptrToControlBlock_->getSharedRefs() == 0 && ptrToControlBlock_->getWeakRefs() == 0) {
            delete ptrToControlBlock_;
        }
    }
}

template <typename T>
int weak_ptr<T>::use_count() const noexcept {
    if (ptrToControlBlock_) {
        return ptrToControlBlock_->getSharedRefs();
    } else
        return 0;
}

template <typename T>
bool weak_ptr<T>::expired() const noexcept {
    if(ptrToControlBlock_)
    {
        return ptrToControlBlock_->getSharedRefs() == 0;
    }
    return true;
}

template <typename T>
shared_ptr<T> weak_ptr<T>::lock() const noexcept {
    shared_ptr<T> tempPtr(*this);
    return tempPtr;
}

template <typename T>
void weak_ptr<T>::reset() noexcept {
    if (ptr_) {
        ptrToControlBlock_->decrementWeakRefs();
    }
    ptr_ = nullptr;
    ptrToControlBlock_ = nullptr;
}

}  // namespace my
