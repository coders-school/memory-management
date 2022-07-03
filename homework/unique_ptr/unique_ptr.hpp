#include <iostream>

template <typename T>
class unique_ptr
{
public:
    unique_ptr() noexcept;
    unique_ptr(T *ptr) noexcept;
    unique_ptr(unique_ptr &) = delete;
    unique_ptr(unique_ptr &&other) noexcept;

    ~unique_ptr();

    unique_ptr &operator=(unique_ptr &) = delete;
    unique_ptr &operator=(unique_ptr &&other) noexcept;

    T &operator*() const noexcept;
    T *operator->() const noexcept;
    T *get() const noexcept;
    T *release() noexcept;
    void reset(T *ptr) noexcept;

private:
    T *ptr_;
};

template <typename T>
unique_ptr<T>::unique_ptr() noexcept : ptr_(nullptr)
{
}

template <typename T>
unique_ptr<T>::unique_ptr(T *ptr) noexcept : ptr_(ptr)
{
}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr &&other) noexcept
{
    if (&other != this)
    {
        ptr_ = std::move(other.ptr_);
    }
    other.ptr_ = nullptr;
}

template <typename T>
unique_ptr<T>::~unique_ptr()
{
    delete ptr_;
}

template <typename T>
unique_ptr<T> &unique_ptr<T>::operator=(unique_ptr &&other) noexcept
{
    if (&other != this)
    {
        ptr_ = std::move(other.ptr_);
        other.ptr_ = nullptr;
    }
    return *this;
}

template <typename T>
T &unique_ptr<T>::operator*() const noexcept
{
    return *ptr_;
}

template <typename T>
T *unique_ptr<T>::operator->() const noexcept
{
    return ptr_;
}

template <typename T>
T *unique_ptr<T>::get() const noexcept
{
    return ptr_;
}

template <typename T>
T *unique_ptr<T>::release() noexcept
{
    T *tempPtr = std::move(ptr_);
    ptr_ = nullptr;
    return tempPtr;
}

template <typename T>
void unique_ptr<T>::reset(T *ptr) noexcept
{
    delete ptr_;
    ptr_ = std::move(ptr);
}
