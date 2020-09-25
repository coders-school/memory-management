
#pragma once

template <typename T>
class my_unique_ptr
{

public:
    T* get() { return ptr_; }

    my_unique_ptr(T* ptr) :  ptr_(ptr) {};

    ~my_unique_ptr() { delete ptr_; }

private:
    T* ptr_ = nullptr;
};
