#pragma once
#include <utility>

template <typename T>
class UniquePointer {
public:
    using pointer = T*;
    using element_type = T;

    UniquePointer() = default;
    explicit UniquePointer(pointer ptr)
        : pointer_(ptr){};

    ~UniquePointer() noexcept {
        delete pointer_;
        pointer_ = nullptr;
    }

    UniquePointer(const UniquePointer&) = delete;
    UniquePointer& operator=(const UniquePointer&) = delete;

    UniquePointer(UniquePointer&& other) noexcept {
        std::swap(pointer_, other.pointer_);
    }

    UniquePointer& operator=(UniquePointer&& other) noexcept {
        reset();
        std::swap(pointer_, other.pointer_);
        return *this;
    }

    const pointer get() const noexcept {
        return pointer_;
    }

    pointer get() noexcept {
        return pointer_;
    }

    void reset(pointer ptr = pointer()) noexcept {
        delete pointer_;
        pointer_ = ptr;
    }

    const UniquePointer& operator*() const noexcept {
        return *get();
    }

    UniquePointer& operator*() noexcept {
        return *get();
    }

private:
    pointer pointer_{nullptr};
};
