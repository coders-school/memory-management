#pragma once
#include <utility>

template <typename T>
class smartPointer{
public:
    smartPointer(const smartPointer& input) = delete;
    
    smartPointer(T* input)
    {
        pointer = input;
    }

    smartPointer(smartPointer&& input) noexcept :
        pointer(std::move(input.pointer))
    { 
        input.pointer = nullptr;
    }

    ~smartPointer()
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
        relase();
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
