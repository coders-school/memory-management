#pragma once

#include "ControlBlock.hpp"
#include "SharedPointer.hpp"

#include <stdexcept>
#include <string>

template <typename T>
class WeakPointer {
public:
    WeakPointer()
        : refCounter_(new ControlBlock()) {}
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
    ControlBlock* refCounter_{nullptr};
    SharedPointer<T> sharedPtr_{nullptr};

    void checkControlBlock();
};

template <typename T>
WeakPointer<T>::WeakPointer(SharedPointer<T>& sharedPtr)
    : sharedPtr_(sharedPtr), refCounter_(sharedPtr.getRefCounter()) {
    --(*refCounter_);
    refCounter_->increaseWeak();
}
/*
template <typename T>
WeakPointer<T>::WeakPointer(WeakPointer& anotherPtr) noexcept
    : refCounter_(anotherPtr.refCounter_), ptr_(anotherPtr.ptr_) {
    ++(*refCounter_);
}

template <typename T>
WeakPointer<T>::WeakPointer(WeakPointer&& anotherPtr) noexcept
    : refCounter_(anotherPtr.refCounter_), ptr_(anotherPtr.ptr_) {
    anotherPtr.ptr_ = nullptr;
    anotherPtr.refCounter_ = nullptr;
}
*/
template <typename T>
WeakPointer<T>::~WeakPointer() {
    // if (refCounter_ != nullptr) {
    // std::cout << "BEFORE: " << refCounter_->getShared() << "\n";
    //     --(*refCounter_);
    // std::cout << "AFTER: " << refCounter_->getShared() << "\n";
    //     checkControlBlock();
    // }
}
template <typename T>
size_t WeakPointer<T>::use_count() {
    return refCounter_->getWeak();
}

template <typename T>
void WeakPointer<T>::reset() {
    sharedPtr_ = nullptr;
    refCounter_ = new ControlBlock();
}

template <typename T>
bool WeakPointer<T>::expired() {
    return refCounter_->getWeak() == 0;
}

template <typename T>
SharedPointer<T> WeakPointer<T>::lock() {
    if (!expired()) {
        return sharedPtr_;
    } else {
        return nullptr;
    }
    //return expired() ? SharedPointer<T>() : SharedPointer<T>(*this);
}

template <typename T>
WeakPointer<T>& WeakPointer<T>::operator=(SharedPointer<T>& anotherPtr) {
    //checkControlBlock();
    refCounter_->increaseWeak();
    sharedPtr_ = anotherPtr;

    return *this;
}
