#pragma once

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

    // UniquePointer& operator*() const noexcept {
    //     return *get();
    // }
};
