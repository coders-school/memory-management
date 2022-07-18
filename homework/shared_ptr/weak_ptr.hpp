#pragma once
#include "shared_ptr.hpp"

namespace my {

template <class T>
class weak_ptr {
public:
    constexpr weak_ptr() noexcept = default;
    weak_ptr(const weak_ptr& other) noexcept
        : data_ptr{other.data_ptr}, control_ptr{other.control_ptr} {
        if (control_ptr) {
            ++control_ptr->weak_refs;
        }
    }

    weak_ptr& operator=(const weak_ptr& other) noexcept {
        if (data_ptr != other.data_ptr) {
            if (control_ptr) {
                --control_ptr->weak_refs;
                clean_up();
            }
            data_ptr = other.data_ptr;
            control_ptr = other.control_ptr;
            if (control_ptr) {
                ++control_ptr->weak_refs;
            }
        }
        return *this;
    }

    explicit weak_ptr(const shared_ptr<T>& other) noexcept
        : data_ptr{other.data_ptr}, control_ptr{other.control_ptr} {
        ++control_ptr->weak_refs;
    }

    weak_ptr& operator=(const shared_ptr<T>& other) noexcept {
        if (data_ptr != other.data_ptr) {
            if (control_ptr) {
                --control_ptr->weak_refs;
                clean_up();
            }
            data_ptr = other.data_ptr;
            control_ptr = other.control_ptr;
            ++control_ptr->weak_refs;
        }
        return *this;
    }

    weak_ptr(weak_ptr&& other) noexcept
        : data_ptr{other.data_ptr}, control_ptr{other.control_ptr} {
        other.data_ptr = nullptr;
        other.control_ptr = nullptr;
    }

    weak_ptr& operator=(weak_ptr&& other) noexcept {
        if (control_ptr) {
            --control_ptr->weak_refs;
            clean_up();
        }
        data_ptr = other.data_ptr;
        control_ptr = other.control_ptr;
        other.data_ptr = nullptr;
        other.control_ptr = nullptr;
        return *this;
    }

    ~weak_ptr() noexcept {
        if (control_ptr) {
            --control_ptr->weak_refs;
            clean_up();
        }
    }

    [[nodiscard]] size_t use_count() const noexcept {
        if (control_ptr) {
            return control_ptr->shared_refs;
        }
        return 0;
    }

    [[nodiscard]] bool expired() const noexcept {
        return !use_count();
    }

    [[nodiscard]] shared_ptr<T> lock() const noexcept {
        if (expired()) {
            return shared_ptr<T>(nullptr);
        }
        ++control_ptr->shared_refs;
        return shared_ptr<T>(data_ptr, control_ptr);
    }

    void reset() noexcept {
        if (control_ptr) {
            --control_ptr->weak_refs;
            clean_up();
            data_ptr = nullptr;
            control_ptr = nullptr;
        }
    }

private:
    T* data_ptr{nullptr};
    typename shared_ptr<T>::control_block* control_ptr{nullptr};

    void clean_up() noexcept {
        if (!control_ptr->made_with_make_shared) {
            if (!control_ptr->weak_refs) {
                if (expired()) {
                    delete control_ptr;
                }
            }
        } else {
            if (!control_ptr->shared_refs && !control_ptr->weak_refs) {
                if (data_ptr) {
                    data_ptr->~T();
                }
                control_ptr->~control_block();
                delete[] (char*)(data_ptr);
            }
        }
    }
};

}  // namespace my
