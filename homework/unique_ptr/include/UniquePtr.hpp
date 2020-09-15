#pragma once

class NullptrDereferenceError : public std::runtime_error {
public:
    NullptrDereferenceError()
        : std::runtime_error{"Cannot dereference nullptr"} {}
};

template <typename T>
class UniquePtr {
public:
    UniquePtr(T* ptr);

    UniquePtr(const UniquePtr<T>&) = delete;
    UniquePtr<T>& operator=(const UniquePtr<T>&) = delete;

    UniquePtr(UniquePtr<T>&& ptr);
    UniquePtr<T>& operator=(UniquePtr<T>&& ptr);

    T operator*() const;
    T* operator->() const;
    T* get();
    T* release();
    void reset(T* ptr);

    ~UniquePtr() {
        delete ptr_;
    }

private:
    T* ptr_;
};

template <typename T>
UniquePtr<T>::UniquePtr(T* ptr)
    : ptr_{ptr} {}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& ptr)
    : ptr_{ptr.release()} {}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& ptr) {
    if (!ptr_) {
        return *this;
    }
    delete ptr_;
    ptr_ = ptr.ptr_;
    ptr.ptr_ = nullptr;
    return *this;
}

template <typename T>
T UniquePtr<T>::operator*() const {
    if (!ptr_) {
        throw NullptrDereferenceError();
    }
    return *ptr_;
}

template <typename T>
T* UniquePtr<T>::operator->() const {
    return ptr_;
}

template <typename T>
T* UniquePtr<T>::get() {
    if (ptr_) {
        return ptr_;
    }
    return nullptr;
}

template <typename T>
T* UniquePtr<T>::release() {
    T* ptr = ptr_;
    delete ptr_;
    ptr_ = nullptr;
    return ptr;
}

template <typename T>
void UniquePtr<T>::reset(T* ptr) {
    if (ptr_) {
        delete ptr_;
    }
    ptr_ = ptr;
}
