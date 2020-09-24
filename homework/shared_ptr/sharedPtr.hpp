#pragma once

#include <atomic>
#include <memory>
#include <string>

template <typename T>
class shared_ptr {
public:
    shared_ptr();
    shared_ptr(T* ptr);
    shared_ptr(shared_ptr& otherPtr);
    shared_ptr(std::weak_ptr<T>& otherPtr);
    // shared_ptr(shared_ptr&& otherPtr);
    ~shared_ptr();

    unsigned int use_count();
    T* get() const;
    T* release();
    void reset(T* newPtr = nullptr);

    T& operator*() const;
    T* operator->() const;
    shared_ptr& operator=(shared_ptr& otherPtr) = delete;
    shared_ptr& operator=(shared_ptr&& otherPtr);

private:
    std::atomic<size_t> shared_refs;
    std::atomic<size_t> weak_refs;

    T* ptr_;
};

template <typename T>
shared_ptr<T>::shared_ptr() : ptr_(nullptr) {}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr) : ptr_(ptr) {
    counter_ = new Counter();
    if (ptr) {
        shared_refs++;
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr& otherPtr) {
    // swap(ptr_, otherPtr.ptr_);
    ptr_ = otherPtr.ptr_;
    shared_refs = otherPtr.shared_refs;
    shared_refs++;
}

template <typename T>
shared_ptr<T>::shared_ptr(std::weak_ptr<T>& otherPtr) {
    ptr_ = std::move(otherPtr);
    // shared_refs = otherPtr.shared_refs;
    weak_refs++;
}
// template <typename T>
// shared_ptr<T>::shared_ptr(shared_ptr&& otherPtr) : ptr_(otherPtr.release()) {}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    shared_refs--;
    if (use_count() == 0 && weak_refs.load() = 0) {
        delete ptr_;
    } else if (use_count() == 0) {
        ptr_.release();
    }
}

template <typename T>
unsigned int shared_ptr<T>::use_count() {
    return shared_refs.load();
}

template <typename T>
T* shared_ptr<T>::get() const {
    return ptr_;
}

template <typename T>
T* shared_ptr<T>::release() {
    T* temp = nullptr;
    std::swap(temp, ptr_);
    return temp;
}

template <typename T>
void shared_ptr<T>::reset(T* newPtr) {
    delete ptr_;
    shared_refs = 0;
    weak_refs = 0;
    ptr_ = newPtr;
}

template <typename T>
T& shared_ptr<T>::operator*() const {
    if (!ptr_) {
        throw NullptrException{};
    };
    return *ptr_;
}

template <typename T>
T* shared_ptr<T>::operator->() const {
    return ptr_;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& otherPtr) {
    if (this != &otherPtr) {
        delete ptr_;
        ptr_ = otherPtr.ptr_;
        otherPtr.ptr_ = nullptr;
    }
    return *this;
}
