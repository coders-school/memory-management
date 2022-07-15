#pragma once
#include <atomic>

namespace my {

template <class T>
class shared_ptr {
    class control_block {
    public:
        control_block() noexcept = default;
        control_block(const control_block&) = delete;
        control_block& operator=(const control_block&) = delete;
        control_block(control_block&&) = delete;
        control_block& operator=(control_block&&) = delete;

        std::atomic<size_t> shared_refs{1};
        std::atomic<size_t> weak_refs{0};
    };

public:
    explicit shared_ptr(T* ptr) noexcept {
        object_ptr = ptr;
        control_ptr = new control_block;
    }

    shared_ptr(const shared_ptr& other) noexcept
        : object_ptr{other.object_ptr}, control_ptr{other.control_ptr} {
        ++control_ptr->shared_refs;
    }

    shared_ptr& operator=(const shared_ptr& other) noexcept {
        if (this != &other) {
            --control_ptr->shared_refs;
            delete_content_if_needed();
            object_ptr = other.object_ptr;
            control_ptr = other.control_ptr;
            ++control_ptr->shared_refs;
        }
        return *this;
    }

    shared_ptr(shared_ptr&& other) noexcept
        : object_ptr{other.object_ptr}, control_ptr{other.control_ptr} {
        other.object_ptr = nullptr;
        other.control_ptr = new control_block;
    }

    shared_ptr& operator=(shared_ptr&& other) noexcept {
        --control_ptr->shared_refs;
        delete_content_if_needed();
        object_ptr = other.object_ptr;
        control_ptr = other.control_ptr;
        other.object_ptr = nullptr;
        other.control_ptr = new control_block;
        return *this;
    }

    ~shared_ptr() noexcept {
        --control_ptr->shared_refs;
        delete_content_if_needed();
    }

    [[nodiscard]] size_t use_count() const noexcept {
        return control_ptr->shared_refs;
    }

    [[nodiscard]] T* get() const noexcept {
        return object_ptr;
    }

private:
    T* object_ptr{nullptr};
    control_block* control_ptr{nullptr};

    inline void delete_content_if_needed() noexcept {
        if (!control_ptr->shared_refs) {
            delete object_ptr;
            if (!control_ptr->weak_refs) {
                delete control_ptr;
            }
        }
    }
};

}  // namespace my
