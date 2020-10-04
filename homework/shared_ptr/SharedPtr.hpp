#pragma once
#include "SharedControlBlock.hpp"

template <typename T>
class SharedPtr {
public:
    SharedPtr<T>() = default;
    SharedPtr<T>(T* ptr);
    SharedPtr(T* ptr, std::function<void(T*)> deleter) ~SharedPtr<T>();
    ~SharedPtr();

private:
    T* ptr_ = nullptr;
    SharedControlBlock<T>* shControlBlock_ = nullptr;
};

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr)
    : ptr_(ptr), shControlBlock_(new SharedControlBlock<T>{}) {}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr, std::function<void(T*)> deleter)
    : ptr_(ptr), shControlBlock_(new SharedControlBlock<T>{deleter}) {}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    if (shControlBlock_ != nullptr) {
        shControlBlock_->decrementSharedRefsCount();
        if (shControlBlock_->getSharedRefsCount == 0) {
            shControlBlock_->defaultDeleter(ptr_);
        } else if (shControlBlock_->getSharedRefsCount == 0 && shControlBlock_->getWeakRefsCount == 0) {
            delete shControlBlock_;
        }
    }
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
// * Copying is allowed - it increments shared_refs
// * Moving is allowed and it means:
//   * Copying original pointers to a new object
//   * Setting source pointer to nullptr
// * Member functions: `operator*()`, `operator->()`, `get()`, `reset()`, `use_count()`, `operator bool()`

// Do not forget about CI - UT + Valgrind / ASAN. Work in pairs.
