#pragma once
#include <utility>

template <typename T>
class SmartPointer{
public:
    SmartPointer(const SmartPointer& input) = delete;
    
    SmartPointer(T* input)
    {
        pointer = input;
    }

    SmartPointer(SmartPointer&& input) noexcept
    { 
        pointer = std::exchange(input.pointer, nullptr);
    }

    ~SmartPointer()
    {
        delete pointer;
    }

    T& operator*() 
    {
        return *pointer;
    }

    T* operator->()
    {
        return pointer;
    }

    T* get() const
    {
        return pointer;
    }

    T* release()
    {
        return std::exchange(pointer, nullptr);
    }

    void reset()
    {
        if (pointer)
            delete pointer;
    }

    void reset(T* input)
    {
        T* old_ptr = std::exchange(pointer, input);
        if (old_ptr)
            delete old_ptr;
    }
    
    operator bool() const
    {
        return !(nullptr==pointer);
    }
    
private:
    T* pointer;
};
