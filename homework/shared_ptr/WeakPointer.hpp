#pragma once

#include <iostream>
#include <stdexcept>

template <typename T>
class WeakPointer;

#include "ControlBlock.hpp"
#include "SharedPointer.hpp"

template <typename T>
class WeakPointer {
public:
    template <typename>
    friend class SharedPointer;
    WeakPointer() noexcept = default;
    explicit WeakPointer(const SharedPointer<T>& sharedPtr);
    WeakPointer(const WeakPointer& anotherPtr);
    WeakPointer(WeakPointer&& anotherPtr) noexcept;
    ~WeakPointer();

    void reset();
    size_t use_count() const noexcept;
    bool expired() const noexcept;
    SharedPointer<T> lock();

    T& operator*() const = delete;
    T* operator->() const = delete;
    WeakPointer<T>& operator=(SharedPointer<T>& anotherPtr);
    WeakPointer<T>& operator=(const WeakPointer<T>& anotherPtr);
    WeakPointer<T>& operator=(WeakPointer<T>&& anotherPtr);

private:
    T* ptr_{nullptr};
    ControlBlockBase<T>* refCounter_{nullptr};

    void checkControlBlock();
};

template <typename T>
WeakPointer<T>::WeakPointer(const SharedPointer<T>& sharedPtr)
    : ptr_(sharedPtr.ptr_), refCounter_(sharedPtr.refCounter_) {
    if (refCounter_) {
        refCounter_->increaseWeak();
    }
}

template <typename T>
WeakPointer<T>::WeakPointer(const WeakPointer& anotherPtr)
    : ptr_(anotherPtr.ptr_), refCounter_(anotherPtr.refCounter_) {
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
        checkControlBlock();
    }
}

template <typename T>
size_t WeakPointer<T>::use_count() const noexcept {
    if (refCounter_) {
        return refCounter_->getShared();
    }
    return 0;
}

template <typename T>
void WeakPointer<T>::reset() {
    checkControlBlock();
    ptr_ = nullptr;
    refCounter_ = nullptr;
}

template <typename T>
bool WeakPointer<T>::expired() const noexcept {
    return use_count() == 0;
}

template <typename T>
SharedPointer<T> WeakPointer<T>::lock() {
    if (!expired()) {
        return SharedPointer<T>(*this);
    }
    return SharedPointer<T>();
}

template <typename T>
WeakPointer<T>& WeakPointer<T>::operator=(SharedPointer<T>& anotherPtr) {
    checkControlBlock();
    ptr_ = anotherPtr.ptr_;
    refCounter_ = anotherPtr.refCounter_;
    refCounter_->increaseWeak();

    return *this;
}

template <typename T>
WeakPointer<T>& WeakPointer<T>::operator=(const WeakPointer<T>& anotherPtr) {
    if (this != &anotherPtr) {
        ptr_ = anotherPtr.ptr_;
        refCounter_ = anotherPtr.refCounter_;
        refCounter_->increaseWeak();
    }
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
    refCounter_->decreaseWeak();
    if (refCounter_->getShared() == 0 && refCounter_->getWeak() == 0) {
        delete refCounter_;
    }
}
