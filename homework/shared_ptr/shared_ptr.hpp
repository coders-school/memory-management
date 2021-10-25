#pragma once 

#include <cstddef>


class weak_ptr;


template<typename T>
class shared_ptr {
public:
    shared_ptr(std::nullptr_t) noexcept;
    shared_ptr(const shared_ptr& ptr) noexcept;
    shared_ptr(shared_ptr&& ptr) noexcept;

    T& operator*() const noexcept { return *ptr_; };
    T* operator->() const noexcept { return ptr_; };
private:

    T* rawPtr_{nullptr};
    
    void deleteStoredPointers();
};

