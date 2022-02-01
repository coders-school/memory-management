#pragma once

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
