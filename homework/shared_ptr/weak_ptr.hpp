#pragma once
#include <atomic>
#include <cstddef>
#include "shared_ptr.hpp"

namespace my {

template <typename Type>
class weak_ptr {
public:
    template <typename OtherType>
    friend class shared_ptr;

    // default constructor
    weak_ptr()
        : pointer_(nullptr), control_block_pointer_(new ControlBlock) {
        control_block_pointer_->weak_refs++;
    }

    // destructor
    ~weak_ptr() noexcept {
        if (control_block_pointer_) {  // address only objects with allocated control block, i.e. not for moved objects
            control_block_pointer_->weak_refs--;
            if (control_block_pointer_->weak_refs == 0 && control_block_pointer_->shared_refs == 0) {
                delete control_block_pointer_;
                control_block_pointer_ = nullptr;
            }
        }
    }

    // copy constructor (weak_ptr)
    weak_ptr(const weak_ptr<Type>& other)
        : pointer_(other.pointer_), control_block_pointer_(other.control_block_pointer_) {
        control_block_pointer_->weak_refs++;
    }

    // copy constructor (shared_ptr)
    weak_ptr(const shared_ptr<Type>& other)
        : pointer_(other.get()), control_block_pointer_(other.getControlBlock()) {
        control_block_pointer_->weak_refs++;
    }

    // copy assignment operator (weak_ptr)
    weak_ptr& operator=(const weak_ptr& other) {
        if (control_block_pointer_) {
            control_block_pointer_->weak_refs--;
            if (control_block_pointer_->weak_refs == 0 && control_block_pointer_->shared_refs == 0) {
                delete control_block_pointer_;
                control_block_pointer_ = nullptr;
            }
        }

        pointer_ = other.pointer_;
        control_block_pointer_ = other.control_block_pointer_;
        control_block_pointer_->weak_refs++;
        return *this;
    }

    // copy assignment operator (shared_ptr)
    weak_ptr& operator=(const my::shared_ptr<Type>& other) {
        if (control_block_pointer_) {
            control_block_pointer_->weak_refs--;
            if (control_block_pointer_->weak_refs == 0 && control_block_pointer_->shared_refs == 0) {
                delete control_block_pointer_;
                control_block_pointer_ = nullptr;
            }
        }

        pointer_ = other.get();
        control_block_pointer_ = other.getControlBlock();
        control_block_pointer_->weak_refs++;
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
        if (control_block_pointer_) {
            control_block_pointer_->weak_refs--;
            if (control_block_pointer_->weak_refs == 0 && control_block_pointer_->shared_refs == 0) {
                delete control_block_pointer_;
                control_block_pointer_ = nullptr;
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

    ControlBlock* getControlBlock() const noexcept {
        return control_block_pointer_;
    }

    void reset(Type* pointer = nullptr) noexcept {
        if (control_block_pointer_) {
            control_block_pointer_->weak_refs--;
        }

        pointer_ = pointer;
        control_block_pointer_ = nullptr;
    }

    size_t use_count() const noexcept {
        return control_block_pointer_->weak_refs;
    }

    bool expired() const noexcept {
        return (!control_block_pointer_ || use_count() == 0);
    }

    shared_ptr<Type> lock() const noexcept {
        return my::shared_ptr<Type>(*this);
    }

private:
    Type* pointer_{nullptr};
    ControlBlock* control_block_pointer_{nullptr};
};
}  // namespace my
