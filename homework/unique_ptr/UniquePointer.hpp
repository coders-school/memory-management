#pragma once

template <class T>
class UniquePtr {
private:
    T* ptr_{};

public:
    UniquePtr(T* newPtr = nullptr);
    UniquePtr(UniquePtr<T>&& newPtr);
    ~UniquePtr();

    UniquePtr<T>& operator=(UniquePtr<T>&& newPtr);

    UniquePtr(const UniquePtr<T>& newPtr) = delete;
    UniquePtr<T>& operator=(const UniquePtr<T>& newPtr) = delete;

    T* get() const { return ptr_; }
    T* release();
    void reset(T* newPtr);

    T& operator*() const { return *ptr_; }
};

template <class T>
UniquePtr<T>::UniquePtr(T* newPtr)
    : ptr_(newPtr) {}

template <class T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& newPtr)
    : ptr_(newPtr.release()) {}

template <class T>
UniquePtr<T>::~UniquePtr() {
    delete ptr_;
}

template <class T>
T* UniquePtr<T>::release() {
    T* tmpPtr = ptr_;
    ptr_ = nullptr;
    return tmpPtr;
}

template <class T>
void UniquePtr<T>::reset(T* newPtr) {
    delete ptr_;
    ptr_ = newPtr;
}

template <class T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& newPtr) {
    if (this != &newPtr) {
        delete ptr_;
        ptr_ = newPtr.ptr_;
        newPtr.ptr_ = nullptr;
    }
    return *this;
}
