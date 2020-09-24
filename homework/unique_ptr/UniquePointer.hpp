#pragma once

class NullPtrException : public std::runtime_error {
public:
    NullPtrException(std::string msg) : std::runtime_error{msg} {}
};

template <typename T>
class UniquePointer {
public:
    UniquePointer(T* ptr = nullptr) : ptr_(ptr) {}
    ~UniquePointer();
    UniquePointer(const UniquePointer&) = delete;
    UniquePointer(UniquePointer&& anotherPtr) noexcept;

    T* get();
    T* release();
    void reset(T* ptr = nullptr);

    T& operator*() const;
    T* operator->() const;
    UniquePointer<T>& operator=(UniquePointer<T>&& anotherPtr);
    UniquePointer<T>& operator=(const UniquePointer<T>&) = delete;

private:
    T* ptr_{nullptr};
};

template <class T>
UniquePointer<T>::~UniquePointer() {
    delete ptr_;
}

template <typename T>
UniquePointer<T>::UniquePointer(UniquePointer&& anotherPtr) noexcept : ptr_(anotherPtr.release()) {}

template <typename T>
T* UniquePointer<T>::get() {
    return ptr_;
}

template <typename T>
T* UniquePointer<T>::release() {
    T* ptr = ptr_;
    ptr_ = nullptr;
    return ptr;
}

template <typename T>
void UniquePointer<T>::reset(T* ptr) {
    delete ptr_;
    ptr_ = ptr;
}

template <typename T>
T& UniquePointer<T>::operator*() const {
    if (!ptr_) {
        throw NullPtrException("Dereference null pointer !");
    }
    return *ptr_;
}

template <typename T>
T* UniquePointer<T>::operator->() const {
    return ptr_;
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
