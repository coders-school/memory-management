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

    T* get() const noexcept
    {
        return ptr_;
    }

private:
    T* ptr_;
};
}
