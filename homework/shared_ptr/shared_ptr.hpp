#pragma once
#include <atomic>
#include <iostream>

struct Counter
{
    std::atomic<size_t> count_ = 1;
    std::atomic<size_t> weak_count = 0;
};

template <typename T>
class my_shared_ptr
{

public:

    my_shared_ptr() : counter_ptr(new Counter()) 
    { 
        ptr_ = nullptr; 
    };

    explicit my_shared_ptr(T* ptr) 
        : ptr_(ptr), 
          counter_ptr(new Counter())
    {};

    my_shared_ptr(const my_shared_ptr<T>& other_shared_ptr) 
        : ptr_(other_shared_ptr.ptr_),
          counter_ptr(other_shared_ptr.counter_ptr)
    {
        counter_ptr->count_++;
    };

    my_shared_ptr(my_shared_ptr<T>&& ptr_moved)
        : ptr_(ptr_moved.ptr_), 
        counter_ptr(ptr_moved.counter_ptr)
    {
            ptr_moved.counter_ptr = nullptr;
            ptr_moved.ptr_ = nullptr;
    }

   ~my_shared_ptr()
    {
        deleter();
    }

    my_shared_ptr<T>& operator=(const my_shared_ptr<T>& other_shared_ptr) 
    {
        if(&other_shared_ptr != this)
        {
            deleter();
            ptr_ = other_shared_ptr.ptr_;
            counter_ptr = other_shared_ptr.counter_ptr;
            counter_ptr->count_++;
        }
        return *this;
    }

    my_shared_ptr<T>& operator=(my_shared_ptr<T>&& some_ptr)
    {
        if (&some_ptr != this)
        {
            deleter();
            ptr_ = some_ptr.ptr_;
            counter_ptr = some_ptr.counter_ptr;
            some_ptr.ptr_ = nullptr;
            some_ptr. counter_ptr = nullptr;
        }
        return *this;
    }

    void reset(T* new_ptr=nullptr)
    {
        deleter();
        ptr_ = new_ptr;
        counter_ptr = new Counter();
    };

    void deleter() 
    {
        if (counter_ptr) 
        {
           counter_ptr->count_--;
           if(counter_ptr->count_ == 0)
           {
               delete ptr_;
           }

            if (counter_ptr->count_ == 0 && counter_ptr->weak_count == 0) 
            {
                delete counter_ptr;
            }
        }
    }  

    T* get() { return ptr_; }
    size_t use_count() 
    { 
        if (ptr_) 
        {
            return counter_ptr->count_;
        } 
        else 
        {
            return 0;
        }
    }

    T& operator*()  const { return *ptr_; };
    T* operator->() const { return ptr_; };
    operator bool() const { return ptr_ != nullptr; }

private:
    T* ptr_ = nullptr;
    Counter* counter_ptr = nullptr;
};