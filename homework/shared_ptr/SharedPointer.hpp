#pragma once

#include <stdexcept>
#include <string>

template <typename T>
class SharedPointer;

#include "ControlBlock.hpp"
#include "WeakPointer.hpp"

class NullPtrException : public std::runtime_error {
public:
    NullPtrException(std::string msg)
        : std::runtime_error{msg} {}
};

template <typename T>
class SharedPointer {
public:
    template <typename>
    friend class WeakPointer;
    template <class M, class... Args>
    friend SharedPointer<M> MakeShared(Args&&... args);

    explicit SharedPointer(std::nullptr_t);
    explicit SharedPointer(T* ptr = nullptr);
    SharedPointer(T* ptr, std::function<void(T*)> deleter);
    explicit SharedPointer(WeakPointer<T>& weakPtr);
    SharedPointer(const SharedPointer& anotherPtr);
    SharedPointer(SharedPointer&& anotherPtr) noexcept;
    SharedPointer(std::nullptr_t, std::function<void(T*)> deleter)
        : refCounter_(new ControlBlock<T>* {nullptr, deleter}) {}

    ~SharedPointer();

    T* get() const;
    void reset(
        T* ptr = nullptr,
        std::function<void(T*)> deleter = [](T* ptrToDelete) { delete ptrToDelete; });
    size_t use_count();

    T& operator*() const;
    T* operator->() const;
    operator bool() const;
    SharedPointer<T>& operator=(const SharedPointer<T>& anotherPtr);
    SharedPointer<T>& operator=(SharedPointer<T>&& anotherPtr);

private:
    SharedPointer(ControlBlockData<T>* refCounter)
    {
        refCounter_ = refCounter;
        ptr_ = refCounter_->getData();
    }

    T* ptr_{nullptr};
    ControlBlockBase<T>* refCounter_{nullptr};

    void checkControlBlock();
};

template <typename T>
SharedPointer<T>::SharedPointer(std::nullptr_t)
    : refCounter_(new ControlBlock<T>{})
{
}

template <typename T>
SharedPointer<T>::SharedPointer(T* ptr)
    : ptr_(ptr), refCounter_(new ControlBlock<T>{ptr})
{
}

template <typename T>
SharedPointer<T>::SharedPointer(T* ptr, std::function<void(T*)> deleter)
    : ptr_(ptr), refCounter_(new ControlBlock<T>{ptr, deleter})
{
}

template <typename T>
SharedPointer<T>::SharedPointer(WeakPointer<T>& weakPtr)
    : ptr_(weakPtr.ptr_), refCounter_(weakPtr.refCounter_)
{
    refCounter_->increaseShared();
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer& anotherPtr)
    : ptr_(anotherPtr.ptr_), refCounter_(anotherPtr.refCounter_)
{
    refCounter_->increaseShared();
}

template <typename T>
SharedPointer<T>::SharedPointer(SharedPointer&& anotherPtr) noexcept
    : ptr_(anotherPtr.ptr_), refCounter_(anotherPtr.refCounter_)
{
    anotherPtr.ptr_ = nullptr;
    anotherPtr.refCounter_ = nullptr;
}

template <typename T>
SharedPointer<T>::~SharedPointer()
{
    checkControlBlock();
}

template <typename T>
T* SharedPointer<T>::get() const
{
    return ptr_;
}

template <typename T>
void SharedPointer<T>::reset(T* ptr, std::function<void(T*)> deleter)
{
    checkControlBlock();
    refCounter_ = new ControlBlock<T>{ptr, deleter};
    ptr_ = ptr;
}

template <typename T>
size_t SharedPointer<T>::use_count()
{
    return refCounter_->getShared();
}

template <typename T>
T& SharedPointer<T>::operator*() const
{
    if (!ptr_) {
        throw NullPtrException("Dereference null pointer !");
    }
    return *ptr_;
}

template <typename T>
T* SharedPointer<T>::operator->() const
{
    return ptr_;
}

template <typename T>
SharedPointer<T>::operator bool() const
{
    return ptr_ != nullptr;
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& anotherPtr)
{
    if (this != &anotherPtr) {
        checkControlBlock();
        ptr_ = anotherPtr.ptr_;
        refCounter_ = anotherPtr.refCounter_;
        refCounter_->increaseShared();
    }

    return *this;
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer<T>&& anotherPtr)
{
    if (this != &anotherPtr) {
        checkControlBlock();
        ptr_ = anotherPtr.ptr_;
        refCounter_ = anotherPtr.refCounter_;
        anotherPtr.ptr_ = nullptr;
        anotherPtr.refCounter_ = nullptr;
    }

    return *this;
}

template <typename T>
void SharedPointer<T>::checkControlBlock()
{
    if (refCounter_) {
        refCounter_->decreaseShared();
        if (refCounter_->getShared() == 0 && refCounter_->getWeak() == 0) {
            delete refCounter_;
        }
    }
}
