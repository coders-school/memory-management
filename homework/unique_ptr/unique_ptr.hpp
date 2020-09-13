#pragma once

namespace cs {

template <typename T>
class unique_ptr {
public:
    unique_ptr(T* ptr);
    unique_ptr(unique_ptr&& previousOwner);
    unique_ptr(const unique_ptr&) = delete;
    ~unique_ptr();

    T* release();
    const T* get() const;
    void reset(T* newPtr);

    T* operator->();
    T& operator*();

private:
    T* ptr_;
};

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr)
    : ptr_(ptr) {
}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& previousOwner) {
    ptr_ = previousOwner.release();
}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    if (ptr_) {
        delete ptr_;
    }
}

template <typename T>
T* unique_ptr<T>::operator->() {
    return ptr_;
}

template <typename T>
T& unique_ptr<T>::operator*() {
    return *ptr_;
}

template <typename T>
const T* unique_ptr<T>::get() const {
    return ptr_;
}

template <typename T>
T* unique_ptr<T>::release() {
    T* tempPtr = ptr_;
    ptr_ = nullptr;

    return tempPtr;
}

template <typename T>
void unique_ptr<T>::reset(T* newPtr) {
    T* oldPtr = ptr_;
    ptr_ = newPtr;
    if (oldPtr) {
        delete oldPtr;
    }
}

}  // namespace cs