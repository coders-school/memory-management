#pragma once

namespace my_pointer {
template <typename T>
class unique_ptr {
public:
    constexpr unique_ptr() noexcept
        : ptr_ { nullptr }
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
