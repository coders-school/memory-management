#pragma once

#include "ControlBlock.hpp"

#include <stdexcept>
#include <string>

class NullPtrException : public std::runtime_error {
public:
    NullPtrException(std::string msg) : std::runtime_error{msg} {}
};

template <typename T>
class SharedPointer {
public:
    SharedPointer(T* ptr = nullptr);
    SharedPointer(SharedPointer& anotherPtr);
    SharedPointer(SharedPointer&& anotherPtr) noexcept;
    ~SharedPointer();

    T* get();
    void reset(T* ptr = nullptr);
    size_t use_count();

    T& operator*() const;
    T* operator->() const;
    SharedPointer<T>& operator=(SharedPointer<T>& anotherPtr);
    SharedPointer<T>& operator=(SharedPointer<T>&& anotherPtr);

private:
    ControlBlock* refCounter_{nullptr};
    T* ptr_{nullptr};

    void checkControlBlock();
};

template <typename T>
SharedPointer<T>::SharedPointer(T* ptr) : ptr_(ptr) {
    if (ptr_) {
        refCounter_ = new ControlBlock();
        ++(*refCounter_);
    }
}

template <typename T>
SharedPointer<T>::SharedPointer(SharedPointer& anotherPtr)
    : refCounter_(anotherPtr.refCounter_), ptr_(anotherPtr.ptr_) {
    ++(*refCounter_);
}

template <typename T>
SharedPointer<T>::SharedPointer(SharedPointer&& anotherPtr) noexcept
    : refCounter_(anotherPtr.refCounter_), ptr_(anotherPtr.ptr_) {
    anotherPtr.ptr_ = nullptr;
    anotherPtr.refCounter_ = nullptr;
}

template <typename T>
SharedPointer<T>::~SharedPointer() {
    if (refCounter_ != nullptr) {
        // std::cout << "BEFORE: " << refCounter_->getShared() << "\n";
        --(*refCounter_);
        // std::cout << "AFTER: " << refCounter_->getShared() << "\n";
        checkControlBlock();
    }
}

template <typename T>
T* SharedPointer<T>::get() {
    return ptr_;
}

template <typename T>
void SharedPointer<T>::reset(T* ptr) {
    if (refCounter_->getShared() == 1) {
        delete ptr_;
    } else {
        refCounter_ = new ControlBlock();
        ++(*refCounter_);
    }
    ptr_ = ptr;
}

template <typename T>
size_t SharedPointer<T>::use_count() {
    return refCounter_->getShared();
}

template <typename T>
T& SharedPointer<T>::operator*() const {
    if (!ptr_) {
        throw NullPtrException("Dereference null pointer !");
    }
    return *ptr_;
}

template <typename T>
T* SharedPointer<T>::operator->() const {
    return ptr_;
}
template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer<T>& anotherPtr) {
    --(*refCounter_);
    checkControlBlock();
    refCounter_ = anotherPtr.refCounter_;
    ptr_ = anotherPtr.ptr_;
    ++(*refCounter_);

    return *this;
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer<T>&& anotherPtr) {
    if (this != &anotherPtr) {
        --(*refCounter_);
        checkControlBlock();
        ptr_ = anotherPtr.ptr_;
        refCounter_ = anotherPtr.refCounter_;
        anotherPtr.ptr_ = nullptr;
        anotherPtr.refCounter_ = nullptr;
    }

    return *this;
}

template <typename T>
void SharedPointer<T>::checkControlBlock() {
    if (refCounter_->getShared() == 0) {
        delete ptr_;
        if (refCounter_->getWeak() == 0) {
            delete refCounter_;
        }
    }
}
