#pragma once
#include <iostream>

struct Counter
{
    size_t count_ = 0;
};

template <typename T>
class my_shared_ptr
{

public:
    explicit my_shared_ptr(T* ptr) : ptr_(ptr)
    {
        if (counter_ptr != nullptr)
        {
            counter_ptr->count_++;
        }
        else
        {
            counter_ptr = new Counter();
            counter_ptr->count_++;
        }
    };

    my_shared_ptr() : counter_ptr(new Counter()) { ptr_ = nullptr; };

    my_shared_ptr(const my_shared_ptr<T>& other_shared_ptr)
    {
        this->ptr_ = other_shared_ptr.ptr_;
        this->counter_ptr = other_shared_ptr.counter_ptr;

        counter_ptr->count_++;
    };

    my_shared_ptr(my_shared_ptr<T>&& ptr_moved)
    {
        ptr_ = ptr_moved.get();
        if (counter_ptr != nullptr)
        {
            counter_ptr->count_ = ptr_moved.getCounter()->count_;
        }
        else
        {
            counter_ptr = new Counter();
            counter_ptr->count_ = ptr_moved.getCounter()->count_;
        }
        ptr_moved.~my_shared_ptr<T>;
    }

    T& operator=(const my_shared_ptr<T>& other_shared_ptr)
    {
        delete ptr_;
        delete counter_ptr;

        this->ptr_ = other_shared_ptr.ptr_;
        this->counter_ptr = other_shared_ptr.counter_ptr;
        if (other_shared_ptr)
        {
            this->counter_ptr->count_++;
        }
    };

    T& operator=(const my_shared_ptr<T>&& some_ptr)
    {
        if (some_ptr != this)
        {
            delete ptr_;
            delete counter_ptr;

            this->ptr_ = some_ptr.ptr_;
            this->counter_ptr = some_ptr.counter_ptr;
            some_ptr.reset(nullptr);
        }
        return *this;
    }

    T* get() { return ptr_; }
    Counter* getCounter() { return counter_ptr; }

    ~my_shared_ptr()
    {
        counter_ptr->count_--;
        if (counter_ptr->count_ == 0)
        {
            if (nullptr != ptr_)
                delete ptr_;
            delete counter_ptr;
        }
    }

    T operator*() { return *ptr_; };
    T* operator->() { return this->ptr_; };

private:
    T* ptr_ = nullptr;
    Counter* counter_ptr = nullptr;
};
