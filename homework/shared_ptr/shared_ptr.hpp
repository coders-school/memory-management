#pragma once
#include <atomic>
#include <functional>

namespace my {

template <class T>
class shared_ptr {
    template <class Y>
    friend class weak_ptr;

    template <class U, typename... Args>
    friend shared_ptr<U> make_shared(Args&&... args);

    class control_block {
    public:
        constexpr explicit control_block(bool make_shared_flag = false) noexcept
            : made_with_make_shared{make_shared_flag} {}
        control_block(const control_block&) = delete;
        control_block& operator=(const control_block&) = delete;
        control_block(control_block&&) = delete;
        control_block& operator=(control_block&&) = delete;

        std::atomic<size_t> shared_refs{1};
        std::atomic<size_t> weak_refs{0};
        bool made_with_make_shared{false};
        void (*data_deleter)(T*) = [](T* ptr) { delete ptr; };  // I would prefer std::function here
    };

public:
    explicit shared_ptr(T* ptr = nullptr) noexcept
        : data_ptr{ptr} {
        control_ptr = new control_block;
    }

    constexpr shared_ptr(T* ptr, void (*deleter)(T*)) noexcept
        : shared_ptr(ptr) {
        control_ptr->data_deleter = deleter;
    }

    shared_ptr(const shared_ptr& other) noexcept
        : data_ptr{other.data_ptr}, control_ptr{other.control_ptr} {
        ++control_ptr->shared_refs;
    }

    shared_ptr& operator=(const shared_ptr& other) noexcept {
        if (data_ptr != other.data_ptr) {
            --control_ptr->shared_refs;
            clean_up();
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
        clean_up();
        data_ptr = other.data_ptr;
        control_ptr = other.control_ptr;
        other.data_ptr = nullptr;
        other.control_ptr = new control_block;
        return *this;
    }

    ~shared_ptr() noexcept {
        --control_ptr->shared_refs;
        clean_up();
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

    void reset(T* other = nullptr) noexcept {
        if (this->get() != other || other == nullptr) {
            --control_ptr->shared_refs;
            clean_up();
            data_ptr = other;
            control_ptr = new control_block;
        }
    }

    void reset(T* other, void (*deleter)(T*)) noexcept {
        reset(other);
        control_ptr->data_deleter = deleter;
    }

private:
    T* data_ptr{nullptr};
    control_block* control_ptr{nullptr};

    shared_ptr(T* data, control_block* control) noexcept
        : data_ptr{data}, control_ptr{control} {
    }

    void clean_up() noexcept {
        if (!control_ptr->made_with_make_shared) {
            if (!control_ptr->shared_refs) {
                std::invoke(control_ptr->data_deleter, data_ptr);
                if (!control_ptr->weak_refs) {
                    delete control_ptr;
                }
            }
        } else {
            if (!control_ptr->shared_refs && !control_ptr->weak_refs) {
                if (data_ptr) {
                    data_ptr->~T();
                }
                control_ptr->~control_block();
                delete[](char*)(data_ptr);
            }
        }
    }
};

}  // namespace my
