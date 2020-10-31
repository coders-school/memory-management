#pragma once
#include <atomic>
#include <functional>
#include "ControlBlock.hpp"
#include "WeakPtr.hpp"
#include <iostream>

namespace cs {
template <typename T>
class WeakPtr;

template <typename T>
class SharedPtr {
public:
    SharedPtr(
        T* ptr = nullptr, std::function<void(T*)> deleter = [](T* ptr = nullptr) { delete ptr; }) noexcept
        : ptr_(ptr), cb_(new ControlBlockData<T>{ptr, deleter}) {}
    SharedPtr(const SharedPtr& ptr) noexcept;
    SharedPtr(SharedPtr&& ptr) noexcept;
    SharedPtr(const cs::WeakPtr<T>& ptr) noexcept;
    ~SharedPtr();

    SharedPtr& operator=(const SharedPtr& ptr) noexcept;
    SharedPtr& operator=(SharedPtr&& ptr) noexcept;
    T& operator*() const noexcept { 
        if(!ptr_)
        std::cout << "\nDUPA\n";
        return *ptr_; 
        }
    T* operator->() const noexcept { return ptr_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    T* get() const noexcept { return ptr_; }
    long useCount() const noexcept { return static_cast<long>(cb_->getSharedCounter()); }
    void reset(T* ptr) noexcept;

private:
    explicit SharedPtr(ControlBlockData<T>* cb) noexcept
        : cb_(cb) { ptr_ = cb->getObject(); };

    void deleteResources();

    template <typename Y, typename... Args>
    friend SharedPtr<Y> make_shared(Args&&... args);

    template <typename>
    friend class cs::WeakPtr;

    T* ptr_ = nullptr;
    ControlBlockData<T>* cb_ = nullptr;
};

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& ptr) noexcept {
    ptr_ = ptr.ptr_;
    cb_ = ptr.cb_;
    cb_->incrementSharedRefCounter();
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& ptr) noexcept {
    ptr_ = ptr.ptr_;
    cb_ = ptr.cb_;
    ptr.ptr_ = nullptr;
    ptr.cb_ = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(const cs::WeakPtr<T>& ptr) noexcept {
    ptr_ = ptr.ptr_;
    cb_ = ptr.cb_;
    cb_->incrementSharedRefCounter();
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    std::cout << "\ndeleteResources form destructor sharedPtr\n";
    deleteResources();
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& ptr) noexcept {
    if (&ptr != this) {
        std::cout << "\ndeleteResources from operator=\n";
        deleteResources();
        ptr_ = ptr.ptr_;
        cb_ = ptr.cb_;
        cb_->incrementSharedRefCounter();
    }
    return *this;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& ptr) noexcept {
    if (&ptr != this) {
        deleteResources();
        ptr_ = ptr.ptr_;
        cb_ = ptr.cb_;
        cb_->setDeleter([&]() { delete ptr_; });
        ptr.ptr_ = nullptr;
        ptr.cb_ = nullptr;
    }
    return *this;
}

template <typename T>
void SharedPtr<T>::reset(T* ptr) noexcept {
    *ptr_ = *ptr;
    delete ptr;
}

template <typename T>
void SharedPtr<T>::deleteResources() {
    if (cb_) {
        cb_->decrementSharedRefCounter();
        if (cb_->getSharedCounter() == 0) {
            //cb_->callDeleter();
            if (cb_->getWeakCounter() == 0) {
                std::cout << "\ndeleteResources in sharedPtr\n";
                delete cb_;
            }
        }
    }
}

template <typename Y, typename... Args>
SharedPtr<Y> make_shared(Args&&... args) {
    return cs::SharedPtr<Y>(new ControlBlockData<Y>(std::forward<decltype(args)>(args)...));
}

}  // namespace cs
