#pragma once

#include <cstddef>

/*** DECLARATION ***/

template <typename T>
class unique_ptr {
public:
    unique_ptr(); // default c'tor
    unique_ptr(std::nullptr_t); // c'tor binding to nullptr
    explicit unique_ptr(T*);       // parametrized  c'tor
    unique_ptr(unique_ptr const&); // copying c'tor
    unique_ptr(unique_ptr&&) noexcept; // moving c'tor
    ~unique_ptr(); // d'ctor

    unique_ptr& operator=(unique_ptr const&) = delete; // copying operator
    unique_ptr& operator=(std::nullptr_t); // assignment binding to nullptr
    unique_ptr& operator=(unique_ptr&&) noexcept; // moving operator
    unique_ptr<T>* operator->(); // access operator
    T& operator*() const; // dereference operator

    T* get() const; // get pointer
    T* release() noexcept; // release pointer
    void reset(T*); // reset pointer

private:
    T* data_;
};

/*** IMPLEMENTATION ***/

// default c'tor
template <typename T>
unique_ptr<T>::unique_ptr()
    : data_(nullptr) {
    std::cout << "# default c'tor" << std::endl;
}
// c'tor binding to nullptr
template <typename T>
unique_ptr<T>::unique_ptr(std::nullptr_t)
    : data_(nullptr) { 
    std::cout << "# c'tor binding to nullptr" << std::endl;
    }
// parametrized  c'tor
template <typename T>
unique_ptr<T>::unique_ptr(T* data)
    : data_(data) {
    std::cout << "# parametrized c'tor" << std::endl;
}
// copying c'tor
template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr const& rhs) {
    std::cout << "# copying c'tor" << std::endl;
    if (rhs.get()) { 
        data_ = new T(*rhs.data_);
    } else {
        data_ = nullptr;
    }
}
// moving c'tor
template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& rhs) noexcept {
    std::cout << "# moving c'tor" << std::endl;
    this->data_ = new T(*rhs.data_);
    delete rhs.data_;
    rhs.data_ = nullptr;
}
// d'ctor
template <typename T>
unique_ptr<T>::~unique_ptr() {
    if (data_ != nullptr) {
        std::cout << "# destructing : " << *data_ << std::endl;
        delete data_;
    } else {
        std::cout << "# nothing to destruct" << std::endl;
    }
}
// assignment binding to nullptr
template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(std::nullptr_t) {
    std::cout << "# assignment bining to nullptr" << std::endl;
    if (data_) {
        delete data_;
        data_ = nullptr;
    }
    return *this;
}
// moving operator
template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& rhs) noexcept {
    std::cout << "# moving operator" << std::endl;
    this->data_ = new T(*rhs.data_);
    delete rhs.data_;
    rhs.data_ = nullptr;
    return *this;
}
// access operator
template <typename T>
unique_ptr<T>* unique_ptr<T>::operator->() {
    std::cout << "# access operator" << std::endl;
    return this; 
}
// dereference operator
template <typename T>
T& unique_ptr<T>::operator*() const {
    return *data_;
}
// get pointer
template <typename T>
T* unique_ptr<T>::get() const {
    if (data_) {
        return data_;
    }
    return nullptr;
}
// release pointer
template <typename T>
T* unique_ptr<T>::release() noexcept {
    T* released = data_;
    delete data_;
    data_ = nullptr;
    return released;
}
// reset pointer
template <typename T>
void unique_ptr<T>::reset(T* data) {
    this->release();
    data_ = data;
}
