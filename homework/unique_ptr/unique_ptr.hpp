#pragma once
#include <utility>

namespace my {
template <typename T>
class unique_ptr {
public:
    unique_ptr() = default;

    explicit unique_ptr(T* ptr)
        : pointer_(ptr){};

    ~unique_ptr() noexcept {
        delete pointer_;
        pointer_ = nullptr;
    }

    unique_ptr(const unique_ptr&) = delete;

    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& other) noexcept {
        delete pointer_;
        pointer_ = nullptr;
        std::swap(pointer_, other.pointer_);
    }

    unique_ptr& operator=(unique_ptr&& other) noexcept {
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
};
}  // namespace my
