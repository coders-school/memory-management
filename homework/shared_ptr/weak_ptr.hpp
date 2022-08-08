#pragma once
#include "shared_ptr.hpp"

namespace my {

class controlBlock;

template <typename T>
class weak_ptr {
    friend class shared_ptr<T>;

public:
    // weak_ptr() noexcept
    //     : ptr_(nullptr), ptrToControlBlock_(nullptr) {
    // }

    // weak_ptr(const shared_ptr<T>& other) noexcept {
    //     ptr_ = other.get();
    //     ptrToControlBlock_ = other.getControlBlockPtr();
    //     if (ptr_) {
    //         ptrToControlBlock_->incrementWeakRefs();
    //     }
    // }

    // weak_ptr(const weak_ptr<T>& other) noexcept {
    //     ptr_ = other.ptr_;
    //     ptrToControlBlock_ = other.ptrToControlBlock_;
    //     if (ptr_ != nullptr) {
    //         ptrToControlBlock_->incrementWeakRefs();
    //     }
    // }

    // weak_ptr(weak_ptr<T>&& other) noexcept {
    //     ptr_ = other.ptr_;
    //     other.ptr_ = nullptr;
    //     ptrToControlBlock_ = other.ptrToControlBlock_;
    //     other.ptrToControlBlock_ = nullptr;
    // }

    // ~weak_ptr() noexcept {
    //     if (ptrToControlBlock_) {
    //         ptrToControlBlock_->decrementWeakRefs();
    //         if (ptrToControlBlock_->getSharedRefs() == 0 && ptrToControlBlock_->getWeakRefs() == 0) {
    //             delete ptrToControlBlock_;
    //         }
    //     }
    // }

    // weak_ptr<T>& operator=(const weak_ptr<T>& other) noexcept {
    //     if (other.ptr_ != this && other.ptr_ != nullptr) {
    //         ptr_ = other.ptr_;
    //         ptrToControlBlock_ = other.ptrToControlBlock_;
    //         ptrToControlBlock_->incrementWeakRefs();
    //     } else if (other.ptr_ != this && other.ptr_ == nullptr) {
    //         ptr_ = nullptr;
    //         ptrToControlBlock_ = nullptr;
    //     }
    // }

    // weak_ptr<T>& operator=(const shared_ptr<T>& other) noexcept {
    //     if (other.ptr_ != this && other.ptr_ != nullptr) {
    //         ptr_ = other.ptr_;
    //         ptrToControlBlock_ = other.ptrToControlBlock_;
    //         ptrToControlBlock_->incrementSharedRefs();
    //     } else if (other.ptr_ != this && other.ptr_ == nullptr) {
    //         ptr_ = nullptr;
    //         ptrToControlBlock_ = nullptr;
    //     }
    // }

    // weak_ptr<T>& operator=(const weak_ptr<T>&& other) noexcept {
    //     if (other.ptr_ != this && other.ptr_ != nullptr) {
    //         ptr_ = other.ptr_;
    //         ptrToControlBlock_ = other.ptrToControlBlock_;
    //         other.ptr_ = nullptr;
    //         other.ptrToControlBlock_ = nullptr;
    //     } else if (other.ptr_ != this && other.ptr_ == nullptr) {
    //         ptr_ = nullptr;
    //         ptrToControlBlock_ = nullptr;
    //     }
    // }

    // int use_count() const noexcept {
    //     if (ptrToControlBlock_) {
    //         return ptrToControlBlock_->getSharedRefs();
    //     } else
    //         return 0;
    // }

    // bool expired() const noexcept {
    //     if (ptrToControlBlock_) {
    //         return ptrToControlBlock_->getSharedRefs() == 0;
    //     }
    //     return true;
    // }

    // shared_ptr<T> lock() const noexcept {
    //     shared_ptr<T> tempPtr(*this);
    //     return tempPtr;
    // }

    // void reset() noexcept {
    //     if (ptr_) {
    //         ptrToControlBlock_->decrementWeakRefs();
    //     }
    //     ptr_ = nullptr;
    //     ptrToControlBlock_ = nullptr;
    // }

private:
    T* ptr_;
    controlBlock* ptrToControlBlock_;
};

}  // namespace my