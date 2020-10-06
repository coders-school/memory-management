#pragma once

template <class T>
class unique_ptr {
private:
    T* ptr_{};

public:
    unique_ptr(T* newPtr = nullptr);
    unique_ptr(unique_ptr<T>&& newPtr);
    ~unique_ptr();

    T* get() const { return ptr_; }
    T* release();
    void reset(T* newPtr = nullptr);

    unique_ptr<T>& operator=(unique_ptr<T>&& newPtr);
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }

    unique_ptr(const unique_ptr<T>& newPtr) = delete;
    unique_ptr<T>& operator=(const unique_ptr<T>& newPtr) = delete;
};

template <class T>
unique_ptr<T>::unique_ptr(T* newPtr)
    : ptr_(newPtr) {}

template <class T>
unique_ptr<T>::unique_ptr(unique_ptr<T>&& newPtr)
    : ptr_(newPtr.release()) {}

template <class T>
unique_ptr<T>::~unique_ptr() {
    delete ptr_;
}

template <class T>
T* unique_ptr<T>::release() {
    T* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
}

template <class T>
void unique_ptr<T>::reset(T* newPtr) {
    delete ptr_;
    ptr_ = newPtr;
    newPtr = nullptr;
}

template <class T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& newPtr) {
    if (this != &newPtr) {
        delete ptr_;
        ptr_ = newPtr.ptr_;
        newPtr.ptr_ = nullptr;
    }
    return *this;
}
