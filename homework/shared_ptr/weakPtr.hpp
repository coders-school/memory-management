#pragma once

#include <atomic>
#include <memory>
#include <string>

template <typename T>
class weak_ptr {
public:
    weak_ptr();
    weak_ptr(T* ptr);
    weak_ptr(weak_ptr& otherPtr);
    weak_ptr(std::weak_ptr<T>& otherPtr);
    // weak_ptr(weak_ptr&& otherPtr);
    ~weak_ptr();

    unsigned int use_count();
    T* get() const;
    T* release();
    void reset(T* newPtr = nullptr);

    T& operator*() const;
    T* operator->() const;
    weak_ptr& operator=(weak_ptr& otherPtr) = delete;
    weak_ptr& operator=(weak_ptr&& otherPtr);

private:
    std::atomic<size_t> weak_refs;
    std::atomic<size_t> weak_refs;

    T* ptr_;
};
