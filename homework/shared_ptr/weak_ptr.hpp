#pragma once
#include <atomic>
#include <cstddef>
#include "shared_ptr.hpp"

namespace my {

template <typename Type>
class weak_ptr {
public:
    weak_ptr() = default;

    explicit weak_ptr(Type* pointer)
        : pointer_(pointer), control_block_pointer_(control_block_pointer_) {
        control_block_pointer_->weak_refs++;
    }

    ~weak_ptr() noexcept {
        if (control_block_pointer_) {  // address only objects with allocated control block, i.e. not for moved objects
            control_block_pointer_->weak_refs--;
        }
    }

    // copy constructor
    weak_ptr(const weak_ptr& other)
        : pointer_(other.pointer_), control_block_pointer_(other.control_block_pointer_) {
        control_block_pointer_->weak_refs++;
    }

    // copy assignment operator
    weak_ptr& operator=(const weak_ptr& other) {
        control_block_pointer_->weak_refs--;

        pointer_ = other.pointer_;
        control_block_pointer_ = other.control_block_pointer_;
        control_block_pointer_->weak_refs++;
        return *this;
    }

    // move constructor
    weak_ptr(weak_ptr&& other) noexcept {
        control_block_pointer_->weak_refs--;

        pointer_ = nullptr;
        control_block_pointer_ = nullptr;
        std::swap(pointer_, other.pointer_);
        std::swap(control_block_pointer_, other.control_block_pointer_);
    }

    // move assignment operator
    weak_ptr& operator=(weak_ptr&& other) noexcept {
        control_block_pointer_->weak_refs--;

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
        control_block_pointer_->weak_refs--;

        pointer_ = pointer;
        control_block_pointer_ = new ControlBlock;
        control_block_pointer_->weak_refs++;
    }

    size_t use_count() const noexcept {
        return control_block_pointer_->weak_refs;
    }

private:
    Type* pointer_{nullptr};
    ControlBlock* control_block_pointer_{nullptr};
};
}  // namespace my
