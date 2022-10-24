#pragma once
#include <utility>

template <typename T>
class UniquePointer {
public:
    using ElementType = T;
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
        delete pointer_;
        pointer_ = nullptr;
        std::swap(pointer_, other.pointer_);
    }

    UniquePointer& operator=(UniquePointer&& other) noexcept {
        delete pointer_;
        pointer_ = nullptr;
        std::swap(pointer_, other.pointer_);
        return *this;
    }

    PointerToConst get() const noexcept {
        return pointer_;
    }

    Pointer get() noexcept {
        return pointer_;
    }

    Pointer release() noexcept {
        auto tempPtr = pointer_;
        delete pointer_;
        pointer_ = nullptr;
        return tempPtr;   
    }

    void reset(Pointer ptr = nullptr) noexcept {
        delete pointer_;
        pointer_ = ptr;
    }

    const ElementType& operator*() const noexcept {
        return *pointer_;
    }

    ElementType& operator*() noexcept {
        return *pointer_;
    }

    PointerToConst operator->() const noexcept {
        return pointer_;
    }

    Pointer operator->() noexcept {
        return pointer_;
    }

private:
    Pointer pointer_{nullptr};
};
