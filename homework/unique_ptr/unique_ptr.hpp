#pragma once
#include <iostream>

template <typename T>
class unique_ptr {
    T* ptr;

public:
    explicit unique_ptr(T* p = nullptr) : ptr(p) {}

    ~unique_ptr() 
    {
        delete ptr;
    }

    unique_ptr(unique_ptr&& src) noexcept : ptr(src.ptr) 
    {
        src.ptr = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& src) noexcept 
    {
        if (this != &src) {
            delete ptr;
            ptr = src.ptr;
            src.ptr = nullptr;
        }
        return *this;
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    T& operator*() const 
    {
        return *ptr;
    }

    T* operator->() const 
    {
        return ptr;
    }

    T* get() const 
    {
        return ptr;
    }

    T* release() 
    {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T* p = nullptr) 
    {
        if (ptr != p) 
        {
            delete ptr;
            ptr = p;
        }
    }
};




