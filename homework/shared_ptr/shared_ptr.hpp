#pragma once
#include <atomic>

namespace my {

template <typename T>
class weak_ptr;

class controlBlock {
public:
    controlBlock() noexcept
        : shared_refs_(1), weak_refs_(0) {
    }

    std::size_t getSharedRefs() const noexcept { return shared_refs_; }
    void incrementSharedRefs() noexcept { shared_refs_ += 1; }
    void decrementSharedRefs() noexcept { shared_refs_ -= 1; }

    std::size_t getWeakRefs() const noexcept { return weak_refs_; }
    void incrementWeakRefs() noexcept { weak_refs_ += 1; }
    void decrementWeakRefs() noexcept { weak_refs_ -= 1; }

private:
    std::atomic<std::size_t> shared_refs_;
    std::atomic<std::size_t> weak_refs_;
};

template <typename T>
class shared_ptr {
public:
    shared_ptr() noexcept;
    shared_ptr(T* ptr) noexcept;
    shared_ptr(const shared_ptr& other) noexcept;
    shared_ptr(shared_ptr&& other) noexcept;
    explicit shared_ptr(const weak_ptr<T>& other) noexcept;

    ~shared_ptr();

    shared_ptr& operator=(shared_ptr&) noexcept;
    shared_ptr& operator=(shared_ptr&& other) noexcept;
    explicit operator bool() const noexcept;

    T& operator*() const noexcept;
    T* operator->() const noexcept;
    T* get() const noexcept;
    T* release() noexcept;
    void reset(T* ptr) noexcept;
    void reset() noexcept;

    int use_count() const noexcept;

    controlBlock* getControlBlockPtr() const noexcept;

private:
    T* ptr_;
    controlBlock* ptrToControlBlock_;
};

template <typename T>
shared_ptr<T>::shared_ptr() noexcept
    : ptr_(nullptr), ptrToControlBlock_{nullptr} {
}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr) noexcept
    : ptr_(ptr) {
    if (ptr_) {
        ptrToControlBlock_ = new controlBlock;
    } else {
        ptrToControlBlock_ = nullptr;
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& other) noexcept {
    if (other.ptr_ == nullptr) {
        ptr_ = nullptr;
        ptrToControlBlock_ = nullptr;
    } else {
        ptr_ = other.ptr_;
        ptrToControlBlock_ = other.ptrToControlBlock_;
        ptrToControlBlock_->incrementSharedRefs();
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& other) noexcept {
    if (&other != this) {
        ptr_ = std::move(other.ptr_);
        ptrToControlBlock_ = std::move(other.ptrToControlBlock_);
        other.ptr_ = nullptr;
        other.ptrToControlBlock_ = nullptr;
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(const weak_ptr<T>& other) noexcept {
    ptr_ = other.ptr_;
    ptrToControlBlock_ = other.ptrToControlBlock_;
    if (ptr_) {
        ptrToControlBlock_->incrementSharedRefs();
    }
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    if (ptrToControlBlock_) {
        ptrToControlBlock_->decrementSharedRefs();
        if (ptrToControlBlock_->getSharedRefs() == 0) {
            delete ptr_;
        }
        if (ptrToControlBlock_->getSharedRefs() == 0 && ptrToControlBlock_->getWeakRefs() == 0) {
            delete ptrToControlBlock_;
        }
    }
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr& other) noexcept {
    if (&other != this && other.ptr_ != nullptr) {
        ptr_ = other.ptr_;
        ptrToControlBlock_ = other.ptrToControlBlock_;
        ptrToControlBlock_->incrementSharedRefs();
        return *this;
    } else if (&other != this && other.ptr_ == nullptr) {
        delete ptr_;
        ptr_ = nullptr;
        delete ptrToControlBlock_;
        return *this;
    }
    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& other) noexcept {
    if (&other != this && other.ptr_ != nullptr) {
        ptr_ = std::move(other.ptr_);
        ptrToControlBlock_ = std::move(other.ptrToControlBlock_);
        other.ptr_ = nullptr;
        other.ptrToControlBlock_ = nullptr;
    } else if (&other != this && other.ptr_ == nullptr) {
        delete ptr_;
        ptr_ = nullptr;
        delete ptrToControlBlock_;
    }
    return *this;
}

template <typename T>
shared_ptr<T>::operator bool() const noexcept {
    return ptr_ != nullptr;
}

template <typename T>
T& shared_ptr<T>::operator*() const noexcept {
    return *ptr_;
}

template <typename T>
T* shared_ptr<T>::operator->() const noexcept {
    return ptr_;
}

template <typename T>
T* shared_ptr<T>::get() const noexcept {
    return ptr_;
}

template <typename T>
T* shared_ptr<T>::release() noexcept {
    T* tempPtr = std::move(ptr_);
    ptr_ = nullptr;
    return tempPtr;
}

template <typename T>
void shared_ptr<T>::reset(T* ptr) noexcept {
    delete ptr_;
    ptr_ = std::move(ptr);
}

template <typename T>
void shared_ptr<T>::reset() noexcept {
    delete ptr_;
    ptr_ = nullptr;
}

template <typename T>
int shared_ptr<T>::use_count() const noexcept {
    if (!ptrToControlBlock_) {
        return 0;
    } else {
        return static_cast<int>(ptrToControlBlock_->getSharedRefs());
    }
}

template <typename T>
controlBlock* shared_ptr<T>::getControlBlockPtr() const noexcept {
    if (!ptrToControlBlock_) {
        return nullptr;
    } else
        return ptrToControlBlock_;
}

}  // namespace my
