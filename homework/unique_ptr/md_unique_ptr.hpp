
#pragma once

template <typename T>
class my_unique_ptr
{

public:
    T* get();
    ~my_unique_ptr(T* ptr){
    
    
    }

private:
    T* t_ptr = nullptr;
} 


inline T* get()
{
    return T*;
}
