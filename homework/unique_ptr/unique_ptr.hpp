#pragma once

namespace my {
template <class T>

class unique_ptr {
private:
    T* ptr_ = nullptr;

public:
    unique_ptr()
        : ptr_(nullptr) {}
    unique_ptr(T* ptr)
        : ptr_(ptr) {}
    unique_ptr(const unique_ptr&) = delete;  // deleted copy ctor
    unique_ptr(unique_ptr&& obj) {
        ptr_ = obj.ptr_;
        obj.ptr_ = nullptr;
    }
    unique_ptr& operator=(const unique_ptr&) = delete;  // deleted copy assignment
    unique_ptr& operator=(unique_ptr&& other) {
        if (other.ptr_ != nullptr) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }
    T* operator->() {
        return ptr_;
    }
    T& operator*() {
        return *(ptr_);
    }
    T* get() const {
        return ptr_;
    }
    T* release() {
        auto newPtr = ptr_;
        ptr_ = nullptr;
        return newPtr;
    }
    void reset(T* newPtr = nullptr) {
        T* tempPtr = ptr_;
        ptr_ = newPtr;
        if (tempPtr != nullptr) {
            delete tempPtr;
            tempPtr = nullptr;
        }
    }
    ~unique_ptr() {
        if (ptr_ != nullptr) {
            delete ptr_;
            ptr_ = nullptr;
        }
    }
};
}  // namespace my