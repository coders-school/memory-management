#pragma once

#include <functional>

namespace cs {
template <typename T>
class shared_ptr;
}  // namespace cs

#include "sharedControlBlock.hpp"
#include "weak_ptr.hpp"

namespace cs {
template <typename T>
class shared_ptr {
public:
    shared_ptr() noexcept = default;
    explicit shared_ptr(std::nullptr_t) noexcept
        : controlBlock_(new SharedControlBlockPtr<T>{}) {}
    explicit shared_ptr(T* ptr)
        : ptr_(ptr), controlBlock_(new SharedControlBlockPtr<T>{ptr}) {}
    shared_ptr(T* ptr, std::function<void(T*)> defDeleter)
        : ptr_(ptr), controlBlock_(new SharedControlBlockPtr<T>{ptr, defDeleter}) {}
    shared_ptr(std::nullptr_t, std::function<void(T*)> defDeleter)
        : controlBlock_(new SharedControlBlockPtr<T>{nullptr, defDeleter}) {}
    explicit shared_ptr(const weak_ptr<T>& weakPtr);

    shared_ptr(const shared_ptr& other) noexcept;
    shared_ptr(shared_ptr&& other) noexcept;
    ~shared_ptr();

    shared_ptr& operator=(const shared_ptr& other) noexcept;
    shared_ptr& operator=(shared_ptr&& other) noexcept;

    T& operator*() const noexcept { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    T* get() const noexcept { return ptr_; }
    size_t use_count() const noexcept;

    void reset(
        T* newPtr = nullptr,
        std::function<void(T*)> newDeleter = [](T* ptrToDelete) { delete ptrToDelete; });

private:
    T* ptr_ = nullptr;
    SharedControlBlock<T>* controlBlock_ = nullptr;

    explicit shared_ptr(SharedControlBlockObj<T>* block)
        : controlBlock_(block) { ptr_ = block->getPtr(); }

    void deleteSeq();
    template <typename>
    friend class weak_ptr;

    template <class _T, class... Args>
    friend shared_ptr<_T> make_shared(Args&&... args);
};

template <typename T>
void shared_ptr<T>::deleteSeq() {
    if (controlBlock_) {
        controlBlock_->decrementSharedRefs();
        if (controlBlock_->getSharedRefs() == 0 && controlBlock_->getWeakRefs() == 0) {
            delete controlBlock_;
        }
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(const weak_ptr<T>& weakPtr)
    : ptr_(weakPtr.ptr_), controlBlock_(weakPtr.controlBlock_) {
    controlBlock_->incrementSharedRefs();
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& other) noexcept
    : ptr_(other.ptr_), controlBlock_(other.controlBlock_) {
    other.controlBlock_->incrementSharedRefs();
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& other) noexcept {
    ptr_ = other.ptr_;
    controlBlock_ = other.controlBlock_;
    other.ptr_ = nullptr;
    other.controlBlock_ = nullptr;
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    deleteSeq();
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& other) noexcept {
    if (this != &other) {
        deleteSeq();

        ptr_ = other.ptr_;
        other.controlBlock_->incrementSharedRefs();
        controlBlock_ = other.controlBlock_;
    }
    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& other) noexcept {
    deleteSeq();

    ptr_ = other.ptr_;
    controlBlock_ = other.controlBlock_;
    other.ptr_ = nullptr;
    other.controlBlock_ = nullptr;
    return *this;
}

template <typename T>
size_t shared_ptr<T>::use_count() const noexcept {
    if (controlBlock_) {
        return controlBlock_->getSharedRefs();
    }
    return 0;
}

template <typename T>
void shared_ptr<T>::reset(T* newPtr, std::function<void(T*)> newDeleter) {
    deleteSeq();

    controlBlock_ = new SharedControlBlockPtr<T>{newPtr, newDeleter};
    ptr_ = newPtr;
}

}  // namespace cs
