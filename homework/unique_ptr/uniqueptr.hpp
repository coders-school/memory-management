#pragma once

template <class T> 
class unique_ptr {

  public:
    unique_ptr();
    ~unique_ptr();
    
    T get();
    T release();
    void reset();

    private: 

    T* raw_ptr
};


