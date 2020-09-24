#pragma once

namespace cs {
template <typename T>
class unique_ptr {
    bool isOwned{true};
    T* data_{nullptr};

   public:
    unique_ptr() = default;
    explicit unique_ptr(T* data);
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& rhs);
    unique_ptr& operator=(const unique_ptr&) = delete;
    unique_ptr& operator=(unique_ptr&& rhs);
    T& operator*() const;
    T* operator->() const;
    T* get() const;
    T* release();
    void reset(T* new_ptr = nullptr);
    ~unique_ptr();
};

template <typename T>
unique_ptr<T>::unique_ptr(T* data) : data_(data) {
}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& rhs) {
    delete data_;
    data_ = rhs.data_;
    isOwned = rhs.isOwned;
    rhs.data_ = nullptr;
    rhs.isOwned = false;
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& rhs) {
    if (this == &rhs) {
        return *this;
    }
    if (isOwned) {
        delete data_;
    }
    data_ = rhs.data_;
    isOwned = rhs.isOwned;
    rhs.data_ = nullptr;
    rhs.isOwned = false;
    return *this;
}

template <typename T>
T& unique_ptr<T>::operator*() const {
    return *data_;
}

template <typename T>
T* unique_ptr<T>::operator->() const {
    return data_;
}

template <typename T>
T* unique_ptr<T>::get() const {
    if (!isOwned) {
        return nullptr;
    }
    return data_;
}

template <typename T>
T* unique_ptr<T>::release() {
    isOwned = false;
    return data_;
}

template <typename T>
void unique_ptr<T>::reset(T* new_ptr) {
    if (isOwned) {
        delete data_;
    }
    data_ = new_ptr;
    isOwned = true;
}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    if (isOwned) {
        delete data_;
    }
}

};  // namespace cs
