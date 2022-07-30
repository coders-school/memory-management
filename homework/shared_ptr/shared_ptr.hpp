#pragma once
#include <atomic>

namespace my {

class controlBlock {
public:
    controlBlock() noexcept
        : shared_refs_(1) {
    }

    std::size_t getSharedRefs() const noexcept { return shared_refs_; }
    void incrementSharedRefs() noexcept { shared_refs_ += 1; }
    void decrementSharedRefs() noexcept { shared_refs_ -= 1; }

private:
    std::atomic<std::size_t> shared_refs_;
};

template <typename T>
class shared_ptr {
public:
    shared_ptr() noexcept
        : ptr_(nullptr), ptrToControlBlock_{nullptr} {
    }

    shared_ptr(T* ptr) noexcept
        : ptr_(ptr) {
        if (ptr_) {
            ptrToControlBlock_ = new controlBlock;
        } else {
            ptrToControlBlock_ = nullptr;
        }
    }

    shared_ptr(const shared_ptr& other) noexcept {
        if (other.ptr_ == nullptr) {
            ptr_ = nullptr;
            ptrToControlBlock_ = nullptr;
        } else {
            ptr_ = other.ptr_;
            ptrToControlBlock_ = other.ptrToControlBlock_;
            ptrToControlBlock_->incrementSharedRefs();
        }
    }

    shared_ptr(shared_ptr&& other) noexcept {
        if (&other != this) {
            ptr_ = std::move(other.ptr_);
            ptrToControlBlock_ = std::move(other.ptrToControlBlock_);
            other.ptr_ = nullptr;
            other.ptrToControlBlock_ = nullptr;
        }
    }

    ~shared_ptr() {
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

    shared_ptr<T>& operator=(shared_ptr& other) noexcept {
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

    shared_ptr<T>& operator=(shared_ptr&& other) noexcept {
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

    operator bool() const noexcept {
        return ptr_ != nullptr;
    }

    T& operator*() const noexcept {
        return *ptr_;
    }

    T* operator->() const noexcept {
        return ptr_;
    }

    T* get() const noexcept {
        return ptr_;
    }

    T* release() noexcept {
        T* tempPtr = std::move(ptr_);
        ptr_ = nullptr;
        return tempPtr;
    }

    void reset(T* ptr) noexcept {
        delete ptr_;
        ptr_ = std::move(ptr);
    }

    void reset() noexcept {
        delete ptr_;
        ptr_ = nullptr;
    }

    int use_count() const noexcept {
        if (!ptrToControlBlock_) {
            return 0;
        } else {
            return static_cast<int>(ptrToControlBlock_->getSharedRefs());
        }
    }

    controlBlock* getControlBlockPtr() const noexcept {
        if (!ptrToControlBlock_) {
            return nullptr;
        } else
            return ptrToControlBlock_;
    }

private:
    T* ptr_;
    controlBlock* ptrToControlBlock_;
};

}  // namespace my