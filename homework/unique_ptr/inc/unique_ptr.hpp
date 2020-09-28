#pragma once

namespace cs {
template <typename T>
class unique_ptr {
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
unique_ptr<T>::unique_ptr(unique_ptr&& rhs) :data_(rhs.release()) {
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& rhs) {
    if (this == &rhs) {
        return *this;
    }
    delete data_;
    data_ = rhs.data_;
    rhs.data_ = nullptr;
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
    return data_;
}

template <typename T>
T* unique_ptr<T>::release() {
    T* temp = data_;
    data_ = nullptr;
    return temp;
}

template <typename T>
void unique_ptr<T>::reset(T* new_ptr) {
    delete data_;
    data_ = new_ptr;
}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    delete data_;
}

};  // namespace cs
