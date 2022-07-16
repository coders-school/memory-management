#pragma once
#include <atomic>
#include <functional>

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
        void (*data_deleter)(T*) = [](T* ptr) { delete ptr; };  // I would prefer std::function here
    };

public:
    explicit shared_ptr(T* ptr) noexcept
        : data_ptr{ptr} {
        control_ptr = new control_block;
    }

    explicit shared_ptr(T* ptr, void (*deleter)(T*)) noexcept
        : shared_ptr(ptr) {
        control_ptr->data_deleter = deleter;
    }

    shared_ptr(const shared_ptr& other) noexcept
        : data_ptr{other.data_ptr}, control_ptr{other.control_ptr} {
        ++control_ptr->shared_refs;
    }

    shared_ptr& operator=(const shared_ptr& other) noexcept {
        if (this != &other) {
            --control_ptr->shared_refs;
            delete_content_if_needed();
            data_ptr = other.data_ptr;
            control_ptr = other.control_ptr;
            ++control_ptr->shared_refs;
        }
        return *this;
    }

    shared_ptr(shared_ptr&& other) noexcept
        : data_ptr{other.data_ptr}, control_ptr{other.control_ptr} {
        other.data_ptr = nullptr;
        other.control_ptr = new control_block;
    }

    shared_ptr& operator=(shared_ptr&& other) noexcept {
        --control_ptr->shared_refs;
        delete_content_if_needed();
        data_ptr = other.data_ptr;
        control_ptr = other.control_ptr;
        other.data_ptr = nullptr;
        other.control_ptr = new control_block;
        return *this;
    }

    ~shared_ptr() noexcept {
        --control_ptr->shared_refs;
        delete_content_if_needed();
    }

    [[nodiscard]] T* operator->() const noexcept {
        return this->get();
    }

    [[nodiscard]] T& operator*() const noexcept {
        return *this->get();
    }

    [[nodiscard]] size_t use_count() const noexcept {
        return control_ptr->shared_refs;
    }

    [[nodiscard]] explicit operator bool() const noexcept {
        return data_ptr;
    }

    [[nodiscard]] T* get() const noexcept {
        return data_ptr;
    }

    void reset(T* other = nullptr) {
        if (this->get() != other || other == nullptr) {
            --control_ptr->shared_refs;
            delete_content_if_needed();
            data_ptr = other;
            control_ptr = new control_block;
        }
    }

    void reset(T* other, void (*deleter)(T*)) {
        reset(other);
        control_ptr->data_deleter = deleter;
    }

private:
    T* data_ptr{nullptr};
    control_block* control_ptr{nullptr};

    inline void delete_content_if_needed() noexcept {
        if (!control_ptr->shared_refs) {
            std::invoke(control_ptr->data_deleter, data_ptr);
            if (!control_ptr->weak_refs) {
                delete control_ptr;
            }
        }
    }
};

}  // namespace my
