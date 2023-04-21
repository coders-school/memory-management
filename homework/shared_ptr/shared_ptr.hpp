#pragma once
#include <atomic>
#include <cstddef>

namespace my {

// void deleter() {}

struct ControlBlock {
    // std::atomic<size_t> shared_refs{0};
    // std::atomic<size_t> weak_refs{0};
    size_t shared_refs{0};
    size_t weak_refs{0};
    // void (*deleter_pointer)(int){nullptr};
};

template <typename Type>
class shared_ptr {
public:
    shared_ptr()
        : pointer_(nullptr), control_block_pointer_(new ControlBlock) {
            this->control_block_pointer_->shared_refs++;
        }

    explicit shared_ptr(Type* pointer)
        : pointer_(pointer), control_block_pointer_(new ControlBlock) {
            this->control_block_pointer_->shared_refs++;
        }

    ~shared_ptr() noexcept {
        if (control_block_pointer_) {  // delete only for objects with allocated control block, i.e. not for moved objects
            this->control_block_pointer_->shared_refs--;
            if (this->control_block_pointer_->shared_refs == 0) {
                if (this->control_block_pointer_->weak_refs == 0) {
                    if (control_block_pointer_) {
                        delete control_block_pointer_;
                        control_block_pointer_ = nullptr;
                    }
                }
                if (pointer_) {
                    delete pointer_;
                    pointer_ = nullptr;
                }
            }
        }
    }

    // copy constructor
    shared_ptr(const shared_ptr& other)
        : pointer_(other.pointer_), control_block_pointer_(other.control_block_pointer_) {
        this->control_block_pointer_->shared_refs++;
    }

    // copy assignment operator
    shared_ptr& operator=(const shared_ptr& other) {
        this->control_block_pointer_->shared_refs--;
        // while overwriting an object we may to erase the last object pointing to a resource
        if (this->control_block_pointer_->shared_refs == 0) {
            if (this->control_block_pointer_->weak_refs == 0) {
                delete control_block_pointer_;
                control_block_pointer_ = nullptr;
            }
            if (pointer_) {
                delete pointer_;
                pointer_ = nullptr;
            }
        }
        this->pointer_ = other.pointer_;
        this->control_block_pointer_ = other.control_block_pointer_;
        this->control_block_pointer_->shared_refs++;
        return *this;
    }

    // move constructor
    shared_ptr(shared_ptr&& other) noexcept {
        delete pointer_;
        delete control_block_pointer_;
        pointer_ = nullptr;
        control_block_pointer_ = nullptr;
        std::swap(pointer_, other.pointer_);
        std::swap(control_block_pointer_, other.control_block_pointer_);
    }

    // move assignment operator
    shared_ptr& operator=(shared_ptr&& other) noexcept {
        delete pointer_;
        pointer_ = nullptr;
        std::swap(pointer_, other.pointer_);
        return *this;
    }

    Type* get() const noexcept {
        return pointer_;
    }

    void reset(Type* pointer = nullptr) noexcept {
        delete pointer_;
        pointer_ = pointer;
    }

    Type& operator*() const noexcept {
        return *pointer_;
    }

    Type* operator->() const noexcept {
        return pointer_;
    }

    size_t use_count() const noexcept {
        return control_block_pointer_->shared_refs;
    }

    // Type* release() noexcept {
    //     auto tempPtr = pointer_;
    //     pointer_ = nullptr;
    //     return tempPtr;
    // }

private:
    Type* pointer_{nullptr};
    ControlBlock* control_block_pointer_{nullptr};
};
}  // namespace my
