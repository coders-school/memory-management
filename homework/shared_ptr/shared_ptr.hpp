#pragma once

#include <atomic>

template<typename T>
class shared_ptr {
public:
    T* get() const { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
private:
    T* ptr_;
    std::atomic<size_t> shared_refs;
    std::atomic<size_t> weak_refs;
};
