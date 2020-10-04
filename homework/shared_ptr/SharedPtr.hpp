#pragma once
#include "SharedControlBlock.hpp"

template <typename T>
class SharedPtr {
public:
    SharedPtr<T>() noexcept = default;
    explicit SharedPtr<T>(T* ptr);
    SharedPtr<T>(T* ptr, std::function<void(T*)> deleter);
    ~SharedPtr<T>();

    SharedPtr<T>(const SharedPtr& otherOtr);
    SharedPtr<T>(SharedPtr&& otherPtr);
    SharedPtr<T>& operator=(const SharedPtr& otherPtr);
    SharedPtr<T>& operator=(SharedPtr&& otherPtr);

    T& operator*() const noexcept { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    T* get() const noexcept { return ptr_; }
    void reset(
        T* newPtr = nullptr,
        std::function<void(T*)> newDeleter = [](T* ptr) { delete ptr; }) noexcept;
    size_t use_count() const noexcept { return shControlBlock_->getSharedRefsCount(); }
    explicit operator bool() const noexcept { return this.get() != nullptr; }

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

template <typename T>
void SharedPtr<T>::reset(T* newPtr, std::function<void(T*)> newDeleter) noexcept {
    handleSharedPtrAndControlBlockDelete();
    ptr_ = newPtr;
    shControlBlock_ = new SharedControlBlock<T>{newDeleter};
}
