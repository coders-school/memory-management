#pragma once
#include <utility>

template <typename T>
class UniquePointer {
public:
    using pointer = T*;
    using element_type = T;
private:
    pointer pointer_{ nullptr };

public:
    UniquePointer() = default;
    explicit UniquePointer(pointer ptr)
        : pointer_(ptr){};

    ~UniquePointer() noexcept {
        delete pointer_;
        pointer_ = nullptr;
    }

    UniquePointer(const UniquePointer&) noexcept = delete;
    UniquePointer& operator=(const UniquePointer&) noexcept = delete;

    UniquePointer(UniquePointer&& other) noexcept {
        std::swap(pointer_, other.pointer_);
    }

    UniquePointer& operator=(UniquePointer&& other) noexcept {
        reset();
        std::swap(pointer_, other.pointer_);
        return *this;
    }

    pointer get() const noexcept {
        return pointer_;
    }
    
    void reset(pointer ptr = pointer()) noexcept {
        delete pointer_;
        pointer_ = ptr;
    }   

    // UniquePointer& operator*() const noexcept {
    //     return *get();
    // }
};
