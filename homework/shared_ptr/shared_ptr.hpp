#pragma once
#include <atomic>

namespace my {

template <typename T>
class shared_ptr {
    class controlBlock {
        friend class shared_ptr;

    public:
        constexpr explicit controlBlock() noexcept {}
        controlBlock(const controlBlock&) = delete;
        controlBlock& operator=(const controlBlock&) = delete;
        controlBlock(controlBlock&&) = delete;
        controlBlock& operator=(controlBlock&&) = delete;

    private:
        std::atomic<std::size_t> shared_refs_{1};
        std::atomic<std::size_t> weak_refs{0};
        void (*deleter_)(T*) = [](T* ptr_) { delete ptr_; };
    };

public:
    shared_ptr(T* ptr = nullptr) noexcept
        : ptr_(ptr) {
        if (ptr_) {
            ptrToControlBlock_ = new controlBlock;
        } else {
            ptrToControlBlock_ = nullptr;
        }
    }

    shared_ptr(T* ptr, void (*deleter)(T*)) noexcept
        : shared_ptr(ptr) {
        ptrToControlBlock_->deleter_ = deleter;
    }

    shared_ptr(const shared_ptr& other) noexcept
        : ptr_(other.ptr_), ptrToControlBlock_(other.ptrToControlBlock_) {
        if (ptr_) {
            ptrToControlBlock_->shared_refs_++;
        }
    }

    shared_ptr(shared_ptr&& other) noexcept {
        if (other.ptr_) {
            ptr_ = other.ptr_;
            ptrToControlBlock_ = other.ptrToControlBlock_;
            other.ptr_ = nullptr;
            other.ptrToControlBlock_ = nullptr;
        }
    }

    ~shared_ptr() {
        if (ptr_ || ptrToControlBlock_) {
            cleanUp();
        }
    }

    shared_ptr& operator=(const shared_ptr& other) noexcept {
        if (ptr_ == other.ptr_) {
        } else if (!ptr_ && !other.ptr_) {
            ptr_ = nullptr; // should be removed
            ptrToControlBlock_ = nullptr; // should be removed
        } else if (!ptr_ && other.ptr_) {
            ptr_ = other.ptr_;
            ptrToControlBlock_ = other.ptrToControlBlock_;
            ptrToControlBlock_->shared_refs_++;
        } else if (ptr_ && !other.ptr_) {
            cleanUp();
            ptr_ = nullptr;
            ptrToControlBlock_ = nullptr;
        } else if (ptr_ && other.ptr_) {
            cleanUp();
            ptr_ = other.ptr_;
            ptrToControlBlock_ = other.ptrToControlBlock_;
            ptrToControlBlock_->shared_refs_++;
        }
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (ptr_ == other.ptr_) {
        } else if (!ptr_ && !other.ptr_) {
            ptr_ = nullptr; // should be removed 
            ptrToControlBlock_ = nullptr; // should be removed
        } else if (!ptr_ && other.ptr_) {
            ptr_ = other.ptr_;
            ptrToControlBlock_ = other.ptrToControlBlock_;
            other.ptr_ = nullptr;
            other.ptrToControlBlock_ = nullptr;
        } else if (ptr_ && !other.ptr_) {
            cleanUp();
            ptr_ = nullptr;
            ptrToControlBlock_ = nullptr;
        } else if (ptr_ && other.ptr_) {
            cleanUp();
            ptr_ = other.ptr_;
            ptrToControlBlock_ = other.ptrToControlBlock_;
            other.ptr_ = nullptr;
            other.ptrToControlBlock_ = nullptr;
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
            return static_cast<int>(ptrToControlBlock_->shared_refs_);
        }
    }

    controlBlock* getControlBlockPtr() const noexcept {
        if (!ptrToControlBlock_) {
            return nullptr;
        } else
            return ptrToControlBlock_;
    }

private:
    T* ptr_{nullptr};
    controlBlock* ptrToControlBlock_{nullptr};

    void cleanUp() {
        ptrToControlBlock_->shared_refs_--;
        if (ptrToControlBlock_->shared_refs_ == 0) {
            std::invoke(ptrToControlBlock_->deleter_, ptr_);
            ptr_ = nullptr;
            delete ptrToControlBlock_;
            ptrToControlBlock_ = nullptr;
        }
    }
};

}  // namespace my