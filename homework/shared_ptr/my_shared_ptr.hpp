#pragma once

template <typename T>
class my_shared_ptr
{

public:
    explicit my_shared_ptr(T* ptr) : ptr_(ptr){};

    my_shared_ptr() { ptr_ = nullptr; };

    my_shared_ptr(const my_shared_ptr<T>&) = delete;

    my_shared_ptr(my_shared_ptr<T>&& ptr_m) { ptr_ = ptr_m.release(); }

    void operator=(const my_shared_ptr<T>&) = delete;

    T* get() { return ptr_; }

    T* release()
    {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    };

    void reset(T* new_ptr)
    {
        delete ptr_;
        ptr_ = new_ptr;
    };

    ~my_shared_ptr() { delete ptr_; }

    T operator*() { return *ptr_; };
    T* operator->() { return this->ptr_; };

private:
    T* ptr_ = nullptr;
};
