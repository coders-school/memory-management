#pragma once
#include <atomic>
#include <cstddef>
#include <utility>

namespace my {

// void deleter() {}

struct ControlBlock {
    std::atomic<size_t> shared_refs{0};
    std::atomic<size_t> weak_refs{0};
    // void (*deleter_pointer)(int){nullptr};
};

template <typename Type>
class shared_ptr {
public:
    shared_ptr()
        : pointer_(nullptr), control_block_pointer_(new ControlBlock) {
            this->control_block_pointer_->shared_refs++;
        }

    explicit shared_ptr(Type* ptr)
        : pointer_(ptr), control_block_pointer_(new ControlBlock) {
            this->control_block_pointer_->shared_refs++;
        }

    ~shared_ptr() noexcept {
        --this->control_block_pointer_->shared_refs;
        if (this->control_block_pointer_->shared_refs == 0) {
            if (this->control_block_pointer_->weak_refs == 0) {
                if (!control_block_pointer_) {
                    delete control_block_pointer_;
                    control_block_pointer_ = nullptr;
                }
            }
            if (!pointer_) {
                delete pointer_;
                pointer_ = nullptr;
            }
        }
    }

    shared_ptr(const shared_ptr& other)
        : pointer_(other.pointer_), control_block_pointer_(other.control_block_pointer_) {
        this->control_block_pointer_->shared_refs++;
    }

    shared_ptr& operator=(const shared_ptr& other) {
        this->pointer_ = other.pointer_;
        this->control_block_pointer_ = other.control_block_pointer_;
        this->control_block_pointer_->shared_refs++;
        return *this;
    }

    shared_ptr(shared_ptr&& other) noexcept {
        delete pointer_;
        pointer_ = nullptr;
        std::swap(pointer_, other.pointer_);
    }

    shared_ptr& operator=(shared_ptr&& other) noexcept {
        delete pointer_;
        pointer_ = nullptr;
        std::swap(pointer_, other.pointer_);
        return *this;
    }

    Type* get() const noexcept {
        return pointer_;
    }

    // Type* release() noexcept {
    //     auto tempPtr = pointer_;
    //     pointer_ = nullptr;
    //     return tempPtr;
    // }

    // void reset(Type* ptr = nullptr) noexcept {
    //     delete pointer_;
    //     pointer_ = ptr;
    // }

    // Type& operator*() const noexcept {
    //     return *pointer_;
    // }

    // Type* operator->() const noexcept {
    //     return pointer_;
    // }

private:
    Type* pointer_{nullptr};
    ControlBlock* control_block_pointer_{nullptr};
};
}  // namespace my
