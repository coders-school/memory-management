#pragma once 


template <typename T>
class uniqe_ptr {
public:
    uniqe_ptr();
    ~uniqe_ptr();

    uniqe_ptr(const uniqe_ptr& other); // copy constructor
    uniqe_ptr(uniqe_ptr&& other) noexcept; // move constructor
    uniqe_ptr& operator = (const uniqe_ptr&); // copy assigment
    uniqe_ptr& operator= (uniqe_ptr&& other) noexcept;  // move assigment

    uniqe_ptr<T> operator*() const noexcept;
    T* operator->() const noexcept;

    T* get();
    T* release();
    T* reset();
private:
    T* var_;
};