#pragma once
#include <utility>

template <typename T>
class UniquePointer {
public:
    using Pointer = T*;
    using PointerToConst = const T*;

    UniquePointer() = default;

    explicit UniquePointer(Pointer ptr)
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

    PointerToConst get() const noexcept {
        return pointer_;
    }

    Pointer get() noexcept {
        return pointer_;
    }

    void reset(Pointer ptr = Pointer()) noexcept {
        delete pointer_;
        pointer_ = ptr;
    }

    const UniquePointer& operator*() const noexcept {
        return *this;
    }

    UniquePointer& operator*() noexcept {
        return *this;
    }

private:
    Pointer pointer_{nullptr};
};
