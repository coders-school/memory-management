#pragma once
#include <stdexcept>
#include <string>

class NullPtrException : public std::runtime_error {
public:
    NullPtrException(std::string msg) : std::runtime_error{msg} {}
};

template <typename T>
class SharedPointer {
public:
    SharedPointer(T* ptr = nullptr) : ptr_(ptr) {
        refCounter_ = new int(1);
    }
    ~SharedPointer();
    SharedPointer(SharedPointer& anotherPtr);
    SharedPointer(SharedPointer&& anotherPtr) noexcept;

    T* get();
    void reset(T* ptr = nullptr);
    int use_count();

    T& operator*() const;
    T* operator->() const;
    SharedPointer<T>& operator=(SharedPointer<T>&& anotherPtr);
    SharedPointer<T>& operator=(SharedPointer<T>& anotherPtr);

private:
    T* ptr_{nullptr};
    int* refCounter_{nullptr};
};

template <class T>
SharedPointer<T>::~SharedPointer() {
    std::cout << "BEFORE: " << *refCounter_ << "\n";
    *refCounter_ -= 1;
    std::cout << "AFTER: " << *refCounter_ << "\n";
    if (*refCounter_ == 0) {
        delete ptr_;
    }
}

template <typename T>
SharedPointer<T>::SharedPointer(SharedPointer& anotherPtr) {
    ptr_ = anotherPtr.ptr_;
    refCounter_ = anotherPtr.refCounter_;
    *refCounter_ += 1;
}

template <typename T>
SharedPointer<T>::SharedPointer(SharedPointer&& anotherPtr) noexcept : ptr_(anotherPtr.release()) {}

template <typename T>
T* SharedPointer<T>::get() {
    return ptr_;
}

template <typename T>
void SharedPointer<T>::reset(T* ptr) {
    delete ptr_;
    ptr_ = ptr;
}

template <typename T>
int SharedPointer<T>::use_count() {
    return *refCounter_;
}

template <typename T>
T& SharedPointer<T>::operator*() const {
    if (!ptr_) {
        throw NullPtrException("Dereference null pointer !");
    }
    return *ptr_;
}

template <typename T>
T* SharedPointer<T>::operator->() const {
    return ptr_;
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer<T>&& anotherPtr) {
    if (this != &anotherPtr) {
        delete ptr_;
        ptr_ = anotherPtr.ptr_;
        anotherPtr.ptr_ = nullptr;
    }

    return *this;
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer<T>& anotherPtr) {
    if (this != &anotherPtr) {
        ptr_ = anotherPtr.ptr_;
        refCounter_ = anotherPtr.refCounter_;
        *refCounter_ += 1;
    }

    return *this;
}
