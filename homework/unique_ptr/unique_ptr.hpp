#pragma once

#include <iostream>
#include <utility>
#include <exception>

template<typename T>
class Unique
{
private:
    T* ptr_;

public:
    Unique() : ptr_(nullptr) {};
    Unique(T* ptr) : ptr_(ptr) {};
    ~Unique() { if(ptr_) delete ptr_; }

    Unique(const Unique&) = delete;
    Unique& operator=(const Unique&) = delete;

    Unique(Unique&& other) noexcept {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }

    Unique& operator=(Unique&& other) noexcept
    {
        if(&other != this)
        {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    T& operator*() const
    {
        if(!ptr_)
            throw std::runtime_error("nullptr!");
        return *ptr_;
    }

    T* operator->() const noexcept
    {
        return ptr_;
    }

    T* get() const noexcept
    {
        return ptr_;
    }

    T* release() noexcept
    {
        T* temp {ptr_};
        ptr_ = nullptr;
        return temp;
    }

    void reset(T* ptr = nullptr) noexcept
    {
        if (ptr_) {
            delete ptr_;
        }
        ptr_ = ptr;
    }
};

