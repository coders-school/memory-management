
/*

(30 XP) Implement your own unique_ptr (simplified).

unique_ptr is a RAII class:

* Holds a pointer to managed object (template class)
* Constructor copies a pointer
* Destructor release memory
* Copying is not allowed
* Moving is allowed and it means:
  * Copying original pointer to a new object
  * Setting source pointer to nullptr
* Member functions: operator*(), operator->(), get(), release(), reset()
* Should be implemented in `unique_ptr.hpp` file inside `my` namespace
* Tests should be written inside `unique_ptr_tests.cpp` using GoogleTest or Catch2
* You should instantiate `unique_ptr` template class in `unique_ptr_tests.cpp` above your test cases,
e.g. `template class my::unique_ptr<int>;` It's needed for code coverage check to work properly.
*/

#include <iostream>

namespace my {

template <class T>
class unique_ptr {
    T* ptr_ = nullptr;

public:
    unique_ptr() noexcept
        : ptr_{nullptr} {
        std::cout << "unique_ptr::Ctor default" << std::endl;
        std::cout << "ptr_ = " << ptr_ << std::endl;
    }

    unique_ptr(T* ptr) noexcept
        : ptr_{ptr} {
        std::cout << "unique_ptr::Ctor" << std::endl;
        std::cout << "ptr_ = " << ptr_ << std::endl;
    }

    unique_ptr(const unique_ptr&) = delete;

    unique_ptr& operator=(unique_ptr<T>&& pointer) noexcept {
        ptr_ = pointer.ptr_;
        pointer.ptr_ = nullptr;
        return *this;
    }

    unique_ptr(unique_ptr<T>&& pointer) noexcept {
        ptr_ = pointer.ptr_;
        pointer.ptr_ = nullptr;
    }

    T* operator->() const noexcept {
        return ptr_;
    }

    bool operator==(std::nullptr_t) const noexcept {
        return ptr_ == nullptr;
    }

    bool operator!=(std::nullptr_t) const noexcept {
        return ptr_ != nullptr;
    }

    T& operator*() const {
        return *ptr_;
    }

    template <typename T1, typename T2>
    friend bool operator==(const unique_ptr<T1>& ptr1, const unique_ptr<T2>& ptr2) noexcept {
        return typeid(T1) == typeid(T2);
    }

    ~unique_ptr() {
        delete ptr_;
    }
};

}  // namespace my