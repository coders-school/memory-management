#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include <iostream>
#include <memory>

namespace ma{ 

template<typename T>
class unique_ptr {

private:
    T *rawPointer_;

public:
    explicit unique_ptr() : rawPointer_(nullptr) {}

    explicit unique_ptr(T *rawPointer) : rawPointer_(rawPointer) {}

    ~unique_ptr() { if (rawPointer_) delete rawPointer_; }

    //move constructor
    unique_ptr(unique_ptr&& sourceUniquePointer) { rawPointer_ = sourceUniquePointer.release(); }

    //copy constructor
    unique_ptr(const unique_ptr& sourceUniquePointer) = delete;

    //copy assignment operator
    unique_ptr& operator=(const unique_ptr& sourceUniquePointer) = delete;

    //move assignment operator
    unique_ptr& operator=(unique_ptr&& sourceUniquePointer) {
        if(this != &sourceUniquePointer) {
            delete rawPointer_;
            rawPointer_ = sourceUniquePointer.rawPointer_;
            sourceUniquePointer.rawPointer_ = nullptr;
        }
        return *this;
    }

    T& operator*() { return *rawPointer_; }

    T* operator->() { return rawPointer_; }

    T* get() { return rawPointer_; }

    T* release() {
        T *tempPointer = rawPointer_;
        rawPointer_ = nullptr;
        return tempPointer;
    }

    void reset(T *newPointer = nullptr) {
        delete rawPointer_;
        rawPointer_ = newPointer;
    }

};

} // namespace ma

#endif