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

    pointer get() const noexcept {
        return pointer_;
    }
    
    void reset(pointer ptr = pointer()) noexcept {
        pointer old_ptr{ pointer_ };
        pointer_ = ptr;
        if(old_ptr) delete old_ptr;
    }   

    // UniquePointer& operator*() const noexcept {
    //     return *get();
    // }
};
