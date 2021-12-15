#pragma once

namespace my_pointer {
template <typename T>
class unique_ptr {
public:
    constexpr unique_ptr() noexcept
        : ptr_ { nullptr }
    {
    }

    explicit unique_ptr(T* ptr) noexcept
        : ptr_ { ptr }
    {
    }

    ~unique_ptr() noexcept
    {
        if (ptr_) {
            delete ptr_;
        }
    }

    T* get() const noexcept
    {
        return ptr_;
    }

    T& operator*() const noexcept
    {
        return *ptr_;
    }

    explicit operator bool() const noexcept
    {
        return ptr_ != nullptr;
    }

    void reset(T* ptr = nullptr) noexcept
    {
        if (ptr_) {
            delete ptr_;
        }
        ptr_ = ptr;
    }

private:
    T* ptr_;
};
}
