#pragma once
#include "SharedControlBlock.hpp"

template <typename T>
class SharedPtr {
public:
    SharedPtr<T>() = default;
    SharedPtr<T>(T* ptr);
    SharedPtr<T>(T* ptr, std::function<void(T*)> deleter);
    ~SharedPtr<T>();

    SharedPtr<T>(const SharedPtr& otherOtr);
    SharedPtr<T>(SharedPtr&& otherPtr);
    SharedPtr<T>& operator=(const SharedPtr& otherPtr);
    SharedPtr<T>& operator=(SharedPtr&& otherPtr);

    void handleSharedPtrAndControlBlockDelete();

private:
    T* ptr_ = nullptr;
    SharedControlBlock<T>* shControlBlock_ = nullptr;
};

template <typename T>
void SharedPtr<T>::handleSharedPtrAndControlBlockDelete() {
    if (shControlBlock_ != nullptr) {
        shControlBlock_->decrementSharedRefsCount();
        if (shControlBlock_->getSharedRefsCount == 0) {
            shControlBlock_->defaultDeleter(ptr_);
        } else if (shControlBlock_->getSharedRefsCount == 0 && shControlBlock_->getWeakRefsCount == 0) {
            delete shControlBlock_;
        }
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr)
    : ptr_(ptr), shControlBlock_(new SharedControlBlock<T>{}) {}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr, std::function<void(T*)> deleter)
    : ptr_(ptr), shControlBlock_(new SharedControlBlock<T>{deleter}) {}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    handleSharedPtrAndControlBlockDelete();
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& otherPtr) {
    ptr_ = otherPtr.ptr_;
    otherPtr.shControlBlock_->incrementSharedRefsCount();
    shControlBlock_ = otherPtr.shControlBlock_;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& otherPtr) {
    ptr_ = otherPtr.ptr_;
    shControlBlock_ = otherPtr.shControlBlock_;
    otherPtr.ptr_ = nullptr;
    otherPtr.shControlBlock_ = nullptr;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& otherPtr) {
    if (&otherPtr != this) {
        handleSharedPtrAndControlBlockDelete();
        ptr_ = otherPtr.ptr_;
        otherPtr.shControlBlock_->incrementSharedRefsCount();
        shControlBlock_ = otherPtr.shControlBlock_;
    }
    return *this;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& otherPtr) {
    if (&otherPtr != this) {
        handleSharedPtrAndControlBlockDelete();
        ptr_ = otherPtr.ptr_;
        shControlBlock_ = otherPtr.shControlBlock_;
        otherPtr.ptr_ = nullptr;
        otherPtr.shControlBlock_ = nullptr;
    }
    return *this;
}

// (50 XP) Implement your own `shared_ptr` (simplified)
// `shared_ptr` is a RAII class:
// // * Holds a pointer to managed object (template class)
// // * Holds a pointer to shared control block with 2 counters and a deleter:
// //   * shared_refs count (as `std::atomic<size_t>`)
// //   * weak_refs count (as `std::atomic<size_t>`)
// //   * deleter (function pointer)
// // *Constructor copies a pointer and allocate the control block
// // * Destructor decrease shared_refs and:
// //   * if shared_refs == 0 -> release the managed object
// //   * if shared_refs == 0 and weak_refs == 0 -> release the control block
//  // * Copying is allowed - it increments shared_refs
// // * Moving is allowed and it means:
// //   * Copying original pointers to a new object
// //   * Setting source pointer to nullptr
// * Member functions: `operator*()`, `operator->()`, `get()`, `reset()`, `use_count()`, `operator bool()`

// Do not forget about CI - UT + Valgrind / ASAN. Work in pairs.
