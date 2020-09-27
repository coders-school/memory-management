#pragma once

namespace cs {
template <typename T>
class shared_ptr {
public:
    shared_ptr(T* ptr);
    shared_ptr(const shared_ptr& ptr) noexcept;  //copy c-tor
    shared_ptr(shared_ptr&& previousOwner);      //move c-tor
    ~shared_ptr();

    //TODO Implement reset, swap
    const T* get() const;

    const T* operator->();
    T& operator*();
    shared_ptr<T>& operator=(const shared_ptr<T>& ptr) noexcept;             //copy assignment
    shared_ptr<T>& operator=(shared_ptr<T>&& previousOwner);  //move assignment

private:
    size_t* counter_;
    T* ptr_{nullptr};
};

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& ptr) noexcept {
    counter_ = ptr.counter_;
    ptr_ = ptr.ptr_;
    *counter_++;
}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr)
    : ptr_(ptr), counter_(new size_t(0)) {
    *counter_++;
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& previousOwner) {
    ptr_ = previousOwner.release();
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    if (*counter_ == 1) {
        *counter_--;
        delete ptr_;
    }
}

template <typename T>
const T* shared_ptr<T>::get() const {
    return ptr_;
}

template <typename T>
const T* shared_ptr<T>::operator->() {
    return ptr_;
}

template <typename T>
T& shared_ptr<T>::operator*() {
    return *ptr_;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& previousOwner) {
    if (this != &previousOwner) {
        *counter_--;
        if (*counter_ == 0) {
            delete ptr_;
            delete counter_;
        }
        ptr_ = previousOwner.ptr_;
        counter_ = previousOwner.counter_;
        previousOwner.ptr_ = nullptr;
        previousOwner.counter_ = nullptr;
    }

    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& ptr) noexcept {
    //TODO check for memory leak
    counter_ = ptr.counter_;
    ptr_ = ptr.ptr_;
    *counter_++;
}

}  // namespace cs
