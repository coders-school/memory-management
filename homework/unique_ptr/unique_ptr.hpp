#pragma once

#include <algorithm>

namespace my_unique_ptr {

template <typename T>
class unique_ptr {
public:
    unique_ptr() noexcept;
    unique_ptr(T* ptr) noexcept;
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& otherUptr) noexcept;
    ~unique_ptr();
    unique_ptr& operator=(const unique_ptr&) = delete;
    unique_ptr& operator=(unique_ptr&& otherUptr) noexcept;
    T* get() const noexcept;
    T* release() noexcept;
    void reset(T* newPtr = nullptr) noexcept;
    T& operator*() const noexcept;
    T* operator->() const noexcept;
    explicit operator bool() const noexcept;

private:
    T* ptr_;
};

template <typename T>
T* unique_ptr<T>::get() const noexcept {
    return ptr_;
}

template <typename T>
unique_ptr<T>::unique_ptr() noexcept
    : ptr_(nullptr) {}

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr) noexcept
    : ptr_(ptr) {}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& otherUptr) noexcept
    : ptr_(otherUptr.ptr_) {
    otherUptr.ptr_ = nullptr;
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& otherUptr) noexcept {
    ptr_ = otherUptr.ptr_;
    otherUptr.ptr_ = nullptr;

    return *this;
}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    delete ptr_;
}

template <typename T>
T* unique_ptr<T>::release() noexcept {
    T* releasedPtr = ptr_;
    ptr_ = nullptr;

    return releasedPtr;
}

template <typename T>
void unique_ptr<T>::reset(T* ptr) noexcept {
    T* oldPtr = ptr_;
    ptr_ = ptr;
    if (oldPtr) {
        delete oldPtr;
    }
}

template <typename T>
T& unique_ptr<T>::operator*() const noexcept {
    return *ptr_;
}

template <typename T>
T* unique_ptr<T>::operator->() const noexcept {
    return ptr_;
}

template <typename T>
unique_ptr<T>::operator bool() const noexcept {
    return static_cast<bool>(ptr_);
}

}  // namespace my_unique_ptr
