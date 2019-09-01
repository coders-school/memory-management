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

    SmartPointer(SmartPointer&& input) noexcept :
        pointer(std::move(input.pointer))
    { 
        input.pointer = nullptr;
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

    T* get()
    {
        return pointer;
    }

    void release()
    {
        if (pointer)
        {
            delete pointer;
            pointer = nullptr;
        }
    }

    void reset()
    {
        release();
    }

    void reset(T* input)
    {
        if (pointer)
            delete pointer;
        pointer = input;
    }
    
    operator bool()
    {
        return !(nullptr==pointer);
    }
    
private:
    T* pointer;
};
