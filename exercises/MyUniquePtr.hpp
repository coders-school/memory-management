#pragma once

#include <type_traits>
#include <iostream>
#include <algorithm>

template<class ptrType>
class MyUniquePtr
{
    ptrType* m_ptr = nullptr;

public:
    MyUniquePtr(ptrType* ptr) 
    : m_ptr(ptr) 
    {};

    explicit MyUniquePtr(const MyUniquePtr&) = delete;

    //MyUniquePtr(MyUniquePtr&& ptr) = default;

    explicit MyUniquePtr(MyUniquePtr&& ptr) : m_ptr(ptr.release()){};

    ~MyUniquePtr()
    {
        if(m_ptr) 
        {
            std::cout << "Variable destructor called" << std::endl;
            delete m_ptr;
        };
    }

    MyUniquePtr& operator=(const MyUniquePtr&) = delete;

    //MyUniquePtr& operator=(MyUniquePtr&& ptr) = default;

    MyUniquePtr& operator=(MyUniquePtr&& ptr) {
        m_ptr = ptr.release();
        return *this;
    };

    ptrType* operator->() const noexcept {
        return m_ptr;
    }

    ptrType& operator*() const noexcept {
        return *m_ptr;
    }

    ptrType* release() noexcept {
        ptrType* t = m_ptr;
        m_ptr = nullptr;
        return t;
    }

    ptrType* get() const noexcept {
        return m_ptr;
    }

    void reset(ptrType* current_ptr) noexcept {
        std::swap(m_ptr, current_ptr);
        delete current_ptr;
    }
};
