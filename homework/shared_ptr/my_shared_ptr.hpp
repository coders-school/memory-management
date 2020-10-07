#pragma once

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
        ptr_ = other_shared_ptr.get();

        counter_ptr = other_shared_ptr.getCounter();

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
        ptr_moved.getCounter()->count_ = 0;
        delete ptr_moved.get();
    }

    T& operator=(const my_shared_ptr<T>& other_shared_ptr)
    {
        ptr_ = other_shared_ptr.get();
        counter_ptr = other_shared_ptr.getCounter();
        counter_ptr->count_++;
    };

    T& operator=(my_shared_ptr<T>&& some_ptr)
    {
        if (some_ptr != this)
        {
            delete ptr_;
            delete counter_ptr;

            ptr_ = some_ptr.get();
            counter_ptr = some_ptr.getCounter();
            some_ptr.reset(nullptr);
        }
        return *this;
    }

    T* get() { return ptr_; }
    Counter* getCounter() { return counter_ptr; }

    void reset(T* new_ptr) // update!!
    {
        delete ptr_;
        ptr_ = new_ptr;
        delete counter_ptr;
        counter_ptr = new Counter();
    };

    ~my_shared_ptr()
    {
        if (ptr_)
        {
            counter_ptr->count_--;
        }
        else if (counter_ptr->count_ == 0)
        {
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
