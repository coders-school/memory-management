#pragma once

#include <cstddef>

template <typename T>
class unique_ptr {
public:
    unique_ptr();
    unique_ptr(std::nullptr_t);
    explicit unique_ptr(T*);
    unique_ptr(unique_ptr const&);
    unique_ptr(unique_ptr&&) noexcept;
    ~unique_ptr();

    unique_ptr& operator=(unique_ptr const&) = delete;
    unique_ptr& operator=(std::nullptr_t);
    unique_ptr& operator=(unique_ptr&&) noexcept;
    unique_ptr<T>* operator->();
    T& operator*() const;

    T* get() const;
    T* release() noexcept;
    void reset(T*);

private:
    T* data_;
};

template <typename T>
unique_ptr<T>::unique_ptr()
    : data_(nullptr) {}

template <typename T>
unique_ptr<T>::unique_ptr(std::nullptr_t)
    : data_(nullptr) {}

template <typename T>
unique_ptr<T>::unique_ptr(T* data)
    : data_(data) {}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr const& rhs) {
    if (rhs.get()) { 
        data_ = new T(*rhs.data_);
    } else {
        data_ = nullptr;
    }
}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& rhs) noexcept {
    this->data_ = new T(*rhs.data_);
    delete rhs.data_;
    rhs.data_ = nullptr;
}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    if (data_ != nullptr) {
        delete data_;
    }
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(std::nullptr_t) {
    if (data_) {
        delete data_;
        data_ = nullptr;
    }
    return *this;
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& rhs) noexcept {
    this->data_ = new T(*rhs.data_);
    delete rhs.data_;
    rhs.data_ = nullptr;
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
    if (data_) {
        return data_;
    }
    return nullptr;
}

template <typename T>
T* unique_ptr<T>::release() noexcept {
    T* released = data_;
    delete data_;
    data_ = nullptr;
    return released;
}

template <typename T>
void unique_ptr<T>::reset(T* data) {
    this->release();
    data_ = data;
}
