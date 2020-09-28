#pragma once

#include <cstddef>

template <typename T>
class unique_ptr {
public:
    unique_ptr();
    explicit unique_ptr(T*);
    unique_ptr(unique_ptr const&) = delete;
    unique_ptr(unique_ptr&&) noexcept;
    ~unique_ptr();

    unique_ptr& operator=(unique_ptr const&) = delete;
    unique_ptr& operator=(unique_ptr&&) noexcept;
    unique_ptr<T>* operator->();
    T& operator*() const;

    T* get() const;
    T* release() noexcept;
    void reset(T* = nullptr);

private:
    T* data_;
};

template <typename T>
unique_ptr<T>::unique_ptr()
    : data_(nullptr) {}

template <typename T>
unique_ptr<T>::unique_ptr(T* data)
    : data_(data) {}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& rhs) noexcept {
    data_ = rhs.data_;
    rhs.data_ = nullptr;
}

template <typename T>
unique_ptr<T>::~unique_ptr() {
        delete data_;
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& rhs) noexcept {
    if (this != &rhs) {
        delete data_;
        data_ = rhs.data_;
        rhs.data_ = nullptr;
    }
    return *this;
}

template <typename T>
unique_ptr<T>* unique_ptr<T>::operator->() {
    return this; 
}

template <typename T>
T& unique_ptr<T>::operator*() const {
    return *data_;
}

template <typename T>
T* unique_ptr<T>::get() const {
        return data_;
}

template <typename T>
T* unique_ptr<T>::release() noexcept {
    T* released = data_;
    data_ = nullptr;
    return released;
}

template <typename T>
void unique_ptr<T>::reset(T* data) {
    delete data_;
    data_ = data;
}
