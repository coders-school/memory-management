#pragma once
#include <atomic>
#include <iostream>

struct Counter
{
    std::atomic<size_t> count_ = 0;
    std::atomic<size_t> weak_count = 0;
};

template <typename T>
class my_shared_ptr
{

public:
    explicit my_shared_ptr(T* ptr) : ptr_(ptr)
    {
            counter_ptr = new Counter();
            counter_ptr->count_++;
            counter_ptr->weak_count++;
    };

    my_shared_ptr() : counter_ptr(new Counter()) { ptr_ = nullptr; };

    my_shared_ptr(const my_shared_ptr<T>& other_shared_ptr) 
        : ptr_(other_shared_ptr.ptr_),
          counter_ptr(other_shared_ptr.counter_ptr)
    {
        counter_ptr->count_++;
        counter_ptr->weak_count++;
    };

    my_shared_ptr(my_shared_ptr<T>&& ptr_moved) :  ptr_(ptr_moved.ptr_)
    {
            counter_ptr = ptr_moved.counter_ptr;
            ptr_moved.ptr_ = nullptr;
    }

    my_shared_ptr<T>& operator=(const my_shared_ptr<T>& other_shared_ptr) 
    {
        std::cout << "operator move assigment" << "\n";
        delete ptr_;
        delete counter_ptr;

        ptr_ = other_shared_ptr.ptr_;
        counter_ptr = other_shared_ptr.counter_ptr;
        if (other_shared_ptr)
        {
            counter_ptr->count_++;
            counter_ptr->weak_count++;
        }
        return *this;
    };

    my_shared_ptr<T>& operator=(my_shared_ptr<T>&& some_ptr)
    {
        if (&some_ptr != this)
        {
            delete ptr_;
            delete counter_ptr;

            ptr_ = some_ptr.ptr_;
            counter_ptr = some_ptr.counter_ptr;
            some_ptr.ptr_ = nullptr;
            some_ptr. counter_ptr = nullptr;
        }
        return *this;
    }

    void reset(T* new_ptr=nullptr)
    {
        delete ptr_;
        counter_ptr->count_ = 0;
        counter_ptr->weak_count = 0;
        ptr_ = new_ptr;
    };


    T* get() { return ptr_; }
    size_t use_count() { return counter_ptr->count_; }

    ~my_shared_ptr()
    {

        if (counter_ptr->count_ == 0 && counter_ptr->weak_count == 0)
        {
            delete ptr_;
            delete counter_ptr;

        }
        else if(counter_ptr->count_ > 0)
        {
            counter_ptr->count_--;
            counter_ptr->weak_count--;
        }
    }

    T& operator*() { return *ptr_; };
    T* operator->() { return ptr_; };
    operator bool() const { return ptr_ != nullptr; }

private:
    T* ptr_ = nullptr;
    Counter* counter_ptr = nullptr;
};
