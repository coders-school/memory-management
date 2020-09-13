#pragma once

template <typename T>
class unique_ptr {
public:
    unique_ptr(T* ptr);
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr(const unique_ptr&& otherPtr);
    ~unique_ptr();

    T operator*() const;
    T operator->() const;
    T get() const;

private:
    T* ptr_;
};

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr)
    : ptr_(ptr) {}

template <typename T>
unique_ptr<T>::unique_ptr(const unique_ptr&& otherPtr)
    : ptr_(otherPtr) {
        otherPtr = nullptr;
    }

template <typename T>
unique_ptr<T>::~unique_ptr() {
    if (ptr_) {
        delete ptr_;
    }
}

template <typename T>
T unique_ptr<T>::operator*() const {
    if (!ptr_) {
        return nullptr;
    }
    return *ptr_;
}

template <typename T>
T unique_ptr<T>::operator->() const {
    if (!ptr_) {
        return nullptr;
    }
    return ptr_;
}

template <typename T>
T unique_ptr<T>::get() const {
    if (!ptr_) {
        return nullptr;
    }
    return ptr_;
}