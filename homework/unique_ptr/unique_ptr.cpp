#include "unique_ptr.h"
#include <iostream>

namespace cs {

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr)
    : ptr_(ptr) {
}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& previousOwner) {
    ptr_ = previousOwner.release();
    std::cout << "move contructor\n";
}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    if (ptr_) {
        delete ptr_;
    }
}

template <typename T>
T* unique_ptr<T>::operator->() {
    return ptr_;
}

template <typename T>
T& unique_ptr<T>::operator*() {
    return *ptr_;
}

template <typename T>
const T* unique_ptr<T>::get() const {
    return ptr_;
}

template <typename T>
T* unique_ptr<T>::release() {
    T* tempPtr = ptr_;
    ptr_ = nullptr;

    return tempPtr;
}

template <typename T>
void unique_ptr<T>::reset(T* newPtr) {
    if (nullptr == newPtr) {
        delete ptr_;
        return;
    }

    T* oldPtr = ptr_;
    ptr_ = newPtr;
    if (oldPtr) {
        delete oldPtr;
    }
}

template class unique_ptr<int>;

}  // namespace cs