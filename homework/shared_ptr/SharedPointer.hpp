#pragma once

#include <stdexcept>
#include <string>

template <typename T>
class SharedPointer;

#include "ControlBlock.hpp"
#include "WeakPointer.hpp"

class NullPtrException : public std::runtime_error {
public:
    NullPtrException(std::string msg) : std::runtime_error{msg} {}
};

template <typename T>
class SharedPointer {
public:
    template <typename>
    friend class WeakPointer;

    SharedPointer(std::nullptr_t);
    SharedPointer(T* ptr = nullptr);
    SharedPointer(T* ptr, std::function<void(T*)> defDeleter);
    SharedPointer(WeakPointer<T>& weakPtr);
    SharedPointer(SharedPointer& anotherPtr);
    SharedPointer(SharedPointer&& anotherPtr) noexcept;
    ~SharedPointer();

    T* get();
    void reset(
        T* ptr = nullptr,
        std::function<void(T*)> newDeleter = [](T* ptrToDelete) { delete ptrToDelete; });
    size_t use_count();

    T& operator*() const;
    T* operator->() const;
    operator bool() const;
    SharedPointer<T>& operator=(SharedPointer<T>& anotherPtr);
    SharedPointer<T>& operator=(SharedPointer<T>&& anotherPtr);

    ControlBlock<T>* getRefCounter();

private:
    T* ptr_{nullptr};
    ControlBlock<T>* refCounter_{nullptr};

    void checkControlBlock();
};

template <typename T>
SharedPointer<T>::SharedPointer(std::nullptr_t) {
    refCounter_ = new ControlBlockPtr<T>{};
}

template <typename T>
SharedPointer<T>::SharedPointer(T* ptr) : ptr_(ptr) {
    if (ptr_) {
        refCounter_ = new ControlBlockPtr<T>();
        refCounter_->increaseShared();
    }
}

template <typename T>
SharedPointer<T>::SharedPointer(T* ptr, std::function<void(T*)> defDeleter) : ptr_(ptr) {
    if (ptr_) {
        refCounter_ = new ControlBlockPtr<T>{ptr, defDeleter};
        refCounter_->increaseShared();
    }
}

template <typename T>
SharedPointer<T>::SharedPointer(WeakPointer<T>& weakPtr) : ptr_(weakPtr.ptr_), refCounter_(weakPtr.refCounter_) {
    refCounter_->increaseShared();
}

template <typename T>
SharedPointer<T>::SharedPointer(SharedPointer& anotherPtr)
    : ptr_(anotherPtr.ptr_), refCounter_(anotherPtr.refCounter_) {
    refCounter_->increaseShared();
}

template <typename T>
SharedPointer<T>::SharedPointer(SharedPointer&& anotherPtr) noexcept
    : ptr_(anotherPtr.ptr_), refCounter_(anotherPtr.refCounter_) {
    anotherPtr.ptr_ = nullptr;
    anotherPtr.refCounter_ = nullptr;
}

template <typename T>
SharedPointer<T>::~SharedPointer() {
    if (refCounter_ != nullptr) {
        refCounter_->decreaseShared();
        checkControlBlock();
    }
}

template <typename T>
T* SharedPointer<T>::get() {
    return ptr_;
}

template <typename T>
void SharedPointer<T>::reset(T* ptr, std::function<void(T*)> newDeleter) {
    if (refCounter_->getShared() == 1) {
        delete ptr_;
    } else {
        refCounter_ = new ControlBlockPtr<T>{ptr, newDeleter};
        refCounter_->increaseShared();
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
SharedPointer<T>::operator bool() const {
    return ptr_ != nullptr;
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer<T>& anotherPtr) {
    refCounter_->decreaseShared();
    checkControlBlock();
    ptr_ = anotherPtr.ptr_;
    refCounter_ = anotherPtr.refCounter_;
    refCounter_->increaseShared();

    return *this;
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer<T>&& anotherPtr) {
    if (this != &anotherPtr) {
        refCounter_->decreaseShared();
        checkControlBlock();
        ptr_ = anotherPtr.ptr_;
        refCounter_ = anotherPtr.refCounter_;
        anotherPtr.ptr_ = nullptr;
        anotherPtr.refCounter_ = nullptr;
    }

    return *this;
}

template <typename T>
ControlBlock<T>* SharedPointer<T>::getRefCounter() {
    return refCounter_;
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
