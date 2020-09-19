#pragma once

class NullPtrException : public std::runtime_error {
public:
    NullPtrException(std::string msg) : std::runtime_error{msg} {}
};

template <typename T>
class UniquePointer {
public:
    UniquePointer(T* ptr);
    UniquePointer();
    ~UniquePointer();
    UniquePointer(const UniquePointer&) = delete;
    UniquePointer(UniquePointer&& anotherPtr);

    T* get();
    T* release();
    void reset(T* ptr);

    T operator*() const;
    T* operator->() const;
    UniquePointer<T>& operator=(UniquePointer<T>&& anotherPtr);
    UniquePointer<T>& operator=(const UniquePointer<T>&) = delete;

private:
    T* ptr_;
};

template <class T>
UniquePointer<T>::UniquePointer() {}

template <class T>
UniquePointer<T>::UniquePointer(T* ptr) : ptr_(ptr) {}

template <class T>
UniquePointer<T>::~UniquePointer() {
    if (ptr_) {
        delete ptr_;
    }
}

template <typename T>
T UniquePointer<T>::operator*() const {
    if (!ptr_) {
        throw NullPtrException("Dereference null pointer !");
    }
    return *ptr_;
}

template <typename T>
UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer<T>&& anotherPtr) {
    if (this != &anotherPtr) {
        delete ptr_;
        ptr_ = anotherPtr.ptr_;
        anotherPtr.ptr_ = nullptr;
    }

    return *this;
}

template <typename T>
T* UniquePointer<T>::operator->() const {
    return ptr_;
}

template <typename T>
T* UniquePointer<T>::get() {
    return ptr_ ? ptr_ : nullptr;
}

template <typename T>
T* UniquePointer<T>::release() {
    T* ptr = ptr_;
    ptr_ = nullptr;
    return ptr;
}

template <typename T>
void UniquePointer<T>::reset(T* ptr) {
    if (ptr_) {
        delete ptr_;
    }
    ptr_ = ptr;
}

template <typename T>
UniquePointer<T>::UniquePointer(UniquePointer&& anotherPtr) {
    ptr_ = anotherPtr.release();
}
