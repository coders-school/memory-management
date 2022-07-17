#include "shared_ptr.hpp"

namespace my {

template <class T>
class weak_ptr {
public:
    weak_ptr() noexcept = default;
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
                delete_control_block_if_needed();
            }
            data_ptr = other.data_ptr;
            control_ptr = other.control_ptr;
            if (control_ptr) {
                ++control_ptr->weak_refs;
            }
        }
        return *this;
    }

    weak_ptr(const shared_ptr<T>& other) noexcept
        : data_ptr{other.data_ptr}, control_ptr{other.control_ptr} {
        ++control_ptr->weak_refs;
    }

    weak_ptr& operator=(const shared_ptr<T>& other) noexcept {
        if (data_ptr != other.data_ptr) {
            if (control_ptr) {
                --control_ptr->weak_refs;
                delete_control_block_if_needed();
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
            delete_control_block_if_needed();
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
            delete_control_block_if_needed();
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
        return shared_ptr<T>(data_ptr, control_ptr);
    }

    void reset() noexcept {
        if (control_ptr) {
            --control_ptr->weak_refs;
            delete_control_block_if_needed();
            data_ptr = nullptr;
            control_ptr = nullptr;
        }
    }

private:
    T* data_ptr{nullptr};
    typename shared_ptr<T>::control_block* control_ptr{nullptr};

    inline void delete_control_block_if_needed() noexcept {
        if (!control_ptr->weak_refs) {
            if (expired()) {
                delete control_ptr;
            }
        }
    }
};

}  // namespace my
