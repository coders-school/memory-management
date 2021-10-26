#pragma once 

#include <cstddef>

#include "controlBlock.hpp"

class weak_ptr;


template<typename T>
class shared_ptr {
public:
    
    
    shared_ptr(T* ptr) : rawPtr_(ptr), cb_(new ControlBlock<T>) {};

    shared_ptr(const shared_ptr& ptr) noexcept;
    shared_ptr(shared_ptr&& ptr) noexcept;
    ~shared_ptr() noexcept;

    T& operator*() const noexcept { return *ptr_; };
    T* operator->() const noexcept { return ptr_; };
    T* get() const noexcept;
    T* reset() noexcept;
    long use_count() const noexcept

private:

    T* rawPtr_{nullptr};
    ControlBlock<T>* cb_{nullptr};
    void deleteStoredPointers();
};

template<typename T>
T* shared_ptr<T>::get() const noexcept {
    return rawPtr_;
}

template<typename T>
T* shared_ptr<T>::reset() noexcept {

}

