#pragma once
#include <utility>

template<typename T>
class unique_ptr
{
private:
    T *ptr_;

public:

    unique_ptr(T& t)
    {
        ptr_ = &t;
    }
    unique_ptr(unique_ptr<T>&& uqptr)
    {
        ptr_= std::move(uqptr.ptr_);
    }
    unique_ptr<T>& operator=(unique_ptr<T>&& uqptr)
    {
        if(this == uqptr) return *this;
        ptr_ = std::move(uqptr.ptr_);
        uqptr.ptr_ = nullptr;
        return *this;
    }
    ~unique_ptr()
    {
        delete ptr_;
    }

    unique_ptr(unique_ptr<T>&) = delete;
    unique_ptr<T>& operator=(unique_ptr<T>&) = delete;

    unique_ptr<T>& operator*() const noexcept
    {
        return *ptr_;
    }

    unique_ptr<T>* operator->() const noexcept
    {
        return ptr_;
    }

    T* get() const noexcept
    {
        return ptr_;
    }

    T* release() noexcept
    {
        return std::exchange(ptr_, nullptr);
    }

    void reset(T* ptr) noexcept
    {
        std::swap(ptr_, ptr);
        delete ptr;
    }
};
