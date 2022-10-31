#pragma once

namespace my_unique_ptr {

template <typename T>
class unique_ptr {
public:
    // TODO: implementation and tests
    unique_ptr() noexcept;
    // TODO: implementation and tests
    unique_ptr(T* ptr) noexcept;
    unique_ptr(const unique_ptr&) = delete;
    // TODO: implementation and tests
    unique_ptr(unique_ptr&& uPtr) noexcept;
    // TODO: implementation and tests
    ~unique_ptr();
    unique_ptr& operator=(const unique_ptr&) = delete;
    // TODO: implementation and tests
    unique_ptr& operator=(unique_ptr&& uPtr) noexcept;
    // TODO: implementation and tests
    T* get() const noexcept;
    // TODO: implementation and tests
    T* release() noexcept;
    // TODO: implementation and tests
    void reset(T* ptr = nullptr) noexcept;
    // TODO: implementation and tests
    void swap(unique_ptr& other) noexcept;
    // TODO: implementation and tests
    explicit operator bool() const noexcept;
    // TODO: implementation and tests
    T* operator->() const noexcept;

private:
    T* ptr_;
};

}  // namespace my_unique_ptr
