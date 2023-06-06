#pragma once
template <class T>

class MyUniquePtr
{
private:
    T * ptr_ = nullptr;
public:
    MyUniquePtr() : ptr_(nullptr){}
    MyUniquePtr(T * ptr) : ptr_(ptr){}
    MyUniquePtr(const MyUniquePtr & ) = delete; // deleted copy ctor
    MyUniquePtr(MyUniquePtr && obj)
    {
        ptr_ = obj.ptr_;
        obj.ptr_ = nullptr;
    }
    MyUniquePtr& operator=(const MyUniquePtr &) = delete; // deleted copy assignment 
    MyUniquePtr& operator=(MyUniquePtr&& other)
    {
        if(other.ptr_ != nullptr)
        {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }
    T* operator->()
    {
        return ptr_;
    }
    T& operator*()
    {
        return *(ptr_);
    }
    T* get() const
    {
        return ptr_;
    }
    T* release()
    {
        auto newPtr = ptr_;
        ptr_ = nullptr;
        return newPtr;
    }
    void reset()
    {
        if(ptr_ != nullptr)
        {
            delete ptr_;
            ptr_ = nullptr;
        }
    }
    ~MyUniquePtr()
    {
        if(ptr_ != nullptr)
        {
            delete ptr_;
        }
    }
};
