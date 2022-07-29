#pragma once
#include <atomic>

namespace my {

template <typename T>
class shared_ptr {
    class controlBlock {
        friend class shared_ptr;

    public:
        controlBlock() noexcept
            : shared_refs_(1) {
        }

        std::size_t getSharedRefs() const noexcept { return shared_refs_; }
        void incrementSharedRefs() noexcept { shared_refs_ += 1; }
        void decrementSharedRefs() noexcept { shared_refs_ -= 1; }

    private:
        std::atomic<std::size_t> shared_refs_;
        void (*deleter)(T*) = [](T* ptr_) { delete ptr_; };
    };

public:
    explicit shared_ptr(T* ptr = nullptr) noexcept
        : ptr_(ptr) {
        ptrToControlBlock_ = new controlBlock;
    }

    constexpr shared_ptr(T* ptr, void (*deleter)(T*)) noexcept
        : shared_ptr(ptr) {
        ptrToControlBlock_->deleter = deleter;
    }

    shared_ptr(const shared_ptr& other) noexcept
        : ptr_(other.ptr_), ptrToControlBlock_(other.ptrToControlBlock_) {
        ptrToControlBlock_->incrementSharedRefs();
    }

    shared_ptr(shared_ptr&& other) noexcept
        : ptr_(other.ptr_), ptrToControlBlock_(other.ptrToControlBlock_) {
        other.ptr_ = nullptr;
        other.ptrToControlBlock_ = nullptr;
    }

    ~shared_ptr() {
        ptrToControlBlock_->decrementSharedRefs();
        cleanUp();
    }

    shared_ptr<T>& operator=(shared_ptr& other) noexcept {
        if (ptr_ != other.ptr) {
            ptrToControlBlock_->decrementSharedRefs();
        }
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

    void cleanUp() {
        if (ptrToControlBlock_->getSharedRefs()) {
            ptrToControlBlock_->deleter(ptr_);
        }
    }
};

}  // namespace my
