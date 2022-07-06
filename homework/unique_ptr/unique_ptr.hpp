#pragma once

namespace my {

template <class T>
class unique_ptr {
public:
    unique_ptr() noexcept = default;
    explicit unique_ptr(T* ptr) noexcept
        : ptr_(ptr) {}

    ~unique_ptr() noexcept {
        delete ptr_;
    }

    unique_ptr(unique_ptr&& other) noexcept {
        ptr_ = other.release();
    }

    unique_ptr& operator=(unique_ptr&& other) noexcept {
        delete ptr_;
        ptr_ = other.release();
        return *this;
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    [[nodiscard]] T* operator->() const noexcept {
        return this->get();
    }

    [[nodiscard]] T& operator*() const noexcept {
        return *this->get();
    }

    [[nodiscard]] explicit operator bool() const noexcept {
        return ptr_;
    }

    [[nodiscard]] T* get() const noexcept {
        return ptr_;
    }

    [[nodiscard]] T* release() noexcept {
        T* temporary = ptr_;
        ptr_ = nullptr;
        return temporary;
    }

    void reset(T* other = nullptr) noexcept {
        delete ptr_;
        ptr_ = other;
    }

    void reset(unique_ptr other) noexcept {
        delete ptr_;
        ptr_ = other.release();
    }

private:
    T* ptr_{nullptr};
};

}  // namespace my
