#pragma once
#include <atomic>
#include <cstddef>
#include <utility>

namespace my {

void deleter() {}

struct ControlBlock {
   std::atomic<size_t> shared_refs{0};
   std::atomic<size_t> weak_refs{0};
   void (*deleter_pointer)(int){nullptr};
};

template <typename T>
class shared_ptr {
public:
    shared_ptr() = default;

    explicit shared_ptr(T* ptr)
        : pointer_(ptr), control_block_pointer_(new ControlBlock) {};

    ~shared_ptr() noexcept {
        delete pointer_;
        pointer_ = nullptr;
    }

    shared_ptr(const shared_ptr&) = delete;

    shared_ptr& operator=(const shared_ptr&) = delete;

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

    T* get() const noexcept {
        return pointer_;
    }

    T* release() noexcept {
        auto tempPtr = pointer_;
        pointer_ = nullptr;
        return tempPtr;
    }

    void reset(T* ptr = nullptr) noexcept {
        delete pointer_;
        pointer_ = ptr;
    }

    T& operator*() const noexcept {
        return *pointer_;
    }

    T* operator->() const noexcept {
        return pointer_;
    }

private:
    T* pointer_{nullptr};
    ControlBlock* control_block_pointer_{nullptr};
};
}  // namespace my
