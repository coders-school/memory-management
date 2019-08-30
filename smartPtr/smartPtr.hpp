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
    { }

    ~smartPointer()
    {
        delete pointer;
    }

    T& operator*() 
    {
        return *pointer;
    }

private:
    T* pointer;
};
