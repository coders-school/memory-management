#pragma once

namespace cs {

template <typename T>
class shared_ptr {
public:
    shared_ptr(T* ptr);

    T& operator*();

private:
    T* ptr_ {nullptr};

};

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr)
    : ptr_(ptr) {}

template <typename T>
T& shared_ptr<T>::operator*() {
    return *ptr_;
}

}  // namespace cs