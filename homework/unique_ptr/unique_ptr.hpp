#pragma once
#include <utility>

namespace my {
    template <typename T>
    class unique_ptr {
    public:
        using ElementType = T;
        using Pointer = T*;
        using PointerToConst = const T*;

        unique_ptr() = default;

        explicit unique_ptr(Pointer ptr)
            : pointer_(ptr){};

        ~unique_ptr() noexcept {
            delete pointer_;
            pointer_ = nullptr;
        }

        unique_ptr(const unique_ptr&) = delete;

        unique_ptr& operator=(const unique_ptr&) = delete;

        unique_ptr(unique_ptr&& other) noexcept {
            delete pointer_;
            pointer_ = nullptr;
            std::swap(pointer_, other.pointer_);
        }

        unique_ptr& operator=(unique_ptr&& other) noexcept {
            delete pointer_;
            pointer_ = nullptr;
            std::swap(pointer_, other.pointer_);
            return *this;
        }

        PointerToConst get() const noexcept {
            return pointer_;
        }

        Pointer get() noexcept {
            return pointer_;
        }

        Pointer release() noexcept {
            auto tempPtr = pointer_;
            delete pointer_;
            pointer_ = nullptr;
            return tempPtr;   
        }

        void reset(Pointer ptr = nullptr) noexcept {
            delete pointer_;
            pointer_ = ptr;
        }

        const ElementType& operator*() const noexcept {
            return *pointer_;
        }

        ElementType& operator*() noexcept {
            return *pointer_;
        }

        PointerToConst operator->() const noexcept {
            return pointer_;
        }

        Pointer operator->() noexcept {
            return pointer_;
        }

    private:
        Pointer pointer_{nullptr};
    };
}
