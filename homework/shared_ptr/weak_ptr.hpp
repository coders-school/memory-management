#pragma once
#include <atomic>
#include <cstddef>

namespace my {

// void deleter() {}

struct ControlBlock {
    std::atomic<size_t> shared_refs{0};
    std::atomic<size_t> weak_refs{0};
    // void (*deleter_pointer)(int){nullptr};
};

template <typename Type>
class weak_ptr {
public:
    weak_ptr()
        : pointer_(nullptr), control_block_pointer_(new ControlBlock) {
        control_block_pointer_->shared_refs++;
    }

    explicit weak_ptr(Type* pointer)
        : pointer_(pointer), control_block_pointer_(new ControlBlock) {
        control_block_pointer_->shared_refs++;
    }

    ~weak_ptr() noexcept {
        if (control_block_pointer_) {  // delete only for objects with allocated control block, i.e. not for moved objects
            control_block_pointer_->shared_refs--;
            if (control_block_pointer_->shared_refs == 0) {
                if (control_block_pointer_->weak_refs == 0) {
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
    weak_ptr(const weak_ptr& other)
        : pointer_(other.pointer_), control_block_pointer_(other.control_block_pointer_) {
        control_block_pointer_->shared_refs++;
    }

    // copy assignment operator
    weak_ptr& operator=(const weak_ptr& other) {
        control_block_pointer_->shared_refs--;
        // while overwriting an object we may to erase the last object pointing to a resource
        if (control_block_pointer_->shared_refs == 0) {
            if (control_block_pointer_->weak_refs == 0) {
                delete control_block_pointer_;
                control_block_pointer_ = nullptr;
            }
            if (pointer_) {
                delete pointer_;
                pointer_ = nullptr;
            }
        }
        pointer_ = other.pointer_;
        control_block_pointer_ = other.control_block_pointer_;
        control_block_pointer_->shared_refs++;
        return *this;
    }

    // move constructor
    weak_ptr(weak_ptr&& other) noexcept {
        pointer_ = nullptr;
        control_block_pointer_ = nullptr;
        std::swap(pointer_, other.pointer_);
        std::swap(control_block_pointer_, other.control_block_pointer_);
    }

    // move assignment operator
    weak_ptr& operator=(weak_ptr&& other) noexcept {
        control_block_pointer_->shared_refs--;
        // while overwriting an object we may to erase the last object pointing to a resource
        if (control_block_pointer_->shared_refs == 0) {
            if (control_block_pointer_->weak_refs == 0) {
                delete control_block_pointer_;
                control_block_pointer_ = nullptr;
            }
            if (pointer_) {
                delete pointer_;
                pointer_ = nullptr;
            }
        }
        pointer_ = nullptr;
        control_block_pointer_ = nullptr;
        std::swap(pointer_, other.pointer_);
        std::swap(control_block_pointer_, other.control_block_pointer_);
        return *this;
    }

    Type* get() const noexcept {
        return pointer_;
    }

    void reset(Type* pointer = nullptr) noexcept {
        control_block_pointer_->shared_refs--;
        // while overwriting an object we may to erase the last object pointing to a resource
        if (control_block_pointer_->shared_refs == 0) {
            if (control_block_pointer_->weak_refs == 0) {
                delete control_block_pointer_;
                control_block_pointer_ = nullptr;
            }
            if (pointer_) {
                delete pointer_;
                pointer_ = nullptr;
            }
        }
        pointer_ = pointer;
        control_block_pointer_ = new ControlBlock;
        control_block_pointer_->shared_refs++;
    }

    size_t use_count() const noexcept {
        return control_block_pointer_->weak_refs;
    }

private:
    Type* pointer_{nullptr};
    ControlBlock* control_block_pointer_{nullptr};
};
}  // namespace my
