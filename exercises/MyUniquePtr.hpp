#pragma once

#include <iostream>
#include <utility>

template<class ptrType>
class MyUniquePtr
{
    ptrType* m_ptr = nullptr;

public:
    MyUniquePtr(ptrType* ptr) 
    : m_ptr(ptr) 
    {};

    MyUniquePtr(const MyUniquePtr&) = delete;

    //MyUniquePtr(MyUniquePtr&& ptr) = default;

    explicit MyUniquePtr(MyUniquePtr&& ptr) : m_ptr(ptr.release()){};

    ~MyUniquePtr() {
        delete m_ptr;
    }

    MyUniquePtr& operator=(const MyUniquePtr&) = delete;

    //MyUniquePtr& operator=(MyUniquePtr&& ptr) = default;

    MyUniquePtr& operator=(MyUniquePtr&& ptr) {
        m_ptr = std::exchange(ptr.m_ptr, nullptr);
        return *this;
    };

    ptrType* operator->() const noexcept {
        return m_ptr;
    }

    ptrType& operator*() const noexcept {
        return *m_ptr;
    }

    ptrType* release() noexcept {
        return std::exchange(m_ptr, nullptr);
    }

    ptrType* get() const noexcept {
        return m_ptr;
    }

    void reset(ptrType* current_ptr) noexcept {
        std::swap(m_ptr, current_ptr);
        delete current_ptr;
    }
};