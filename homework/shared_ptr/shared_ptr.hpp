#pragma once

namespace cs {

template <typename T>
class shared_ptr {
public:
    shared_ptr(T* ptr);
    shared_ptr(const shared_ptr& otherPtr) noexcept; //copy c-tor
    // shared_ptr(shared_ptr&& previousOwner); //move c-tor
    ~shared_ptr();

    shared_ptr& operator=(const shared_ptr& otherPtr) noexcept;

    T* release();
    const T* get() const;

    const T* operator->();
    T& operator*();

private:
    T* ptr_ {nullptr};

};

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr)
    : ptr_(ptr) {}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& otherPtr) noexcept {
    ptr_ = otherPtr.ptr_;
}

// template <typename T>
// shared_ptr<T>::shared_ptr(shared_ptr&& previousOwner) {
//     ptr_ = previousOwner.release();
// }

template <typename T>
shared_ptr<T>::~shared_ptr() {
    //delete ptr_;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& otherPtr) noexcept {}

template <typename T>
T* shared_ptr<T>::release() {
    T* tempPtr = ptr_;
    ptr_ = nullptr;
    return tempPtr;
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

}  // namespace cs