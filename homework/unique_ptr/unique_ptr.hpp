#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class unique_ptr
{
public:
    unique_ptr();
    explicit unique_ptr(T* ptr);
    ~unique_ptr();
    
    /* copy semantics */
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(unique_ptr& other) = delete;
    unique_ptr& operator=(std::nullptr_t) noexcept;

    /* move semantics */
    unique_ptr(unique_ptr&& other);
    unique_ptr& operator=(unique_ptr&& other);

    /* operator overloading */
    T& operator*() const;
    T* operator->() const;

    /* helper methods */
    T* get() const;
    T* release();
    void reset(T* ptr = nullptr);

private:
    T* ptr_;
};

/*** implementation ***/
template <typename T>
unique_ptr<T>::unique_ptr() : ptr_(nullptr) {}

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr) : ptr_(ptr) {}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    delete ptr_;
}

/* copy semantics */
template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(std::nullptr_t) noexcept
{
    reset(); 
    return *this;
}

/* move semantics */
template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr<T>&& other)
    : ptr_(other.release()) {}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& other)
{
    if (this != &other) {
        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    return *this;
}

/* operator overloading */
template <typename T>
T& unique_ptr<T>::operator*() const
{
    if (!ptr_) {
        throw std::runtime_error("nullptr");
    };
    return *ptr_;
}

template <typename T>
T* unique_ptr<T>::operator->() const
{
    return ptr_;
}

/* helper methods */
template <typename T>
T* unique_ptr<T>::get() const
{
    return ptr_;
}

template <typename T>
T* unique_ptr<T>::release()
{
    T* temp{};
    std::swap(temp, ptr_);
    return temp;
}

template <typename T>
void unique_ptr<T>::reset(T* ptr)
{
    delete ptr_;
    ptr_ = ptr;
}
