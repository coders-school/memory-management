#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class weak_ptr;

#include "ControlBlock.hpp"
#include "SharedPointer.hpp"

template <typename T>
class WeakPointer {
public:
    template <typename>
    friend class SharedPointer;
    WeakPointer() noexcept = default;
    WeakPointer(SharedPointer<T>& sharedPtr);
    WeakPointer(WeakPointer& anotherPtr);
    WeakPointer(WeakPointer&& anotherPtr) noexcept;
    ~WeakPointer();

    void swap(WeakPointer& anotherPtr);
    void reset();
    size_t use_count();
    bool expired();
    SharedPointer<T> lock();

    T& operator*() const = delete;
    T* operator->() const = delete;
    WeakPointer<T>& operator=(SharedPointer<T>& anotherPtr);
    WeakPointer<T>& operator=(WeakPointer<T>& anotherPtr);
    WeakPointer<T>& operator=(WeakPointer<T>&& anotherPtr);

private:
    T* ptr_{nullptr};
    ControlBlock* refCounter_{nullptr};

    void checkControlBlock();
};

template <typename T>
WeakPointer<T>::WeakPointer(SharedPointer<T>& sharedPtr) : ptr_(sharedPtr.ptr_), refCounter_(sharedPtr.refCounter_) {
    if (refCounter_) {
        refCounter_->increaseWeak();
    }
}

template <typename T>
WeakPointer<T>::WeakPointer(WeakPointer& anotherPtr) : ptr_(anotherPtr.ptr_), refCounter_(anotherPtr.refCounter_) {
    if (refCounter_) {
        refCounter_->increaseWeak();
    }
}

template <typename T>
WeakPointer<T>::WeakPointer(WeakPointer&& anotherPtr) noexcept
    : ptr_{anotherPtr.ptr_}, refCounter_{anotherPtr.refCounter_} {
    anotherPtr.ptr_ = nullptr;
    anotherPtr.refCounter_ = nullptr;
}

template <typename T>
WeakPointer<T>::~WeakPointer() {
    if (refCounter_ != nullptr) {
        // std::cout << "BEFORE: " << refCounter_->getWeak() << "\n";
        refCounter_->decreaseWeak();
        // std::cout << "AFTER: " << refCounter_->getWeak() << "\n";
        checkControlBlock();
    }
}

template <typename T>
size_t WeakPointer<T>::use_count() {
    if (refCounter_) {
        return refCounter_->getWeak();
    }
    return 0;
}

template <typename T>
void WeakPointer<T>::reset() {
    refCounter_->decreaseWeak();
    checkControlBlock();
    ptr_ = nullptr;
    refCounter_ = nullptr;
}

template <typename T>
bool WeakPointer<T>::expired() {
    return use_count() == 0;
}

template <typename T>
SharedPointer<T> WeakPointer<T>::lock() {
    if (!expired()) {
        return SharedPointer<T>(*this);
    }
    return nullptr;
}

template <typename T>
WeakPointer<T>& WeakPointer<T>::operator=(SharedPointer<T>& anotherPtr) {
    ptr_ = anotherPtr.ptr_;
    refCounter_ = anotherPtr.refCounter_;
    refCounter_->increaseWeak();

    return *this;
}

template <typename T>
WeakPointer<T>& WeakPointer<T>::operator=(WeakPointer<T>& anotherPtr) {
    ptr_ = anotherPtr.ptr_;
    refCounter_ = anotherPtr.refCounter_;
    refCounter_->increaseWeak();

    return *this;
}

template <typename T>
WeakPointer<T>& WeakPointer<T>::operator=(WeakPointer<T>&& anotherPtr) {
    if (this != &anotherPtr) {
        ptr_ = anotherPtr.ptr_;
        refCounter_ = anotherPtr.refCounter_;
        anotherPtr.ptr_ = nullptr;
        anotherPtr.refCounter_ = nullptr;
    }

    return *this;
}

template <typename T>
void WeakPointer<T>::checkControlBlock() {
    if (refCounter_->getShared() == 0 && refCounter_->getWeak() == 0) {
        delete ptr_;
        delete refCounter_;
    }
}
