#pragma once
namespace pq {

template <typename T>
class unique_ptr {
private:
    T* ptr_;

public:
    //copy c-tor for raw pointer
    unique_ptr(T* Resource) noexcept
        : ptr_{Resource} {}

    //d-tor
    ~unique_ptr() {
        delete ptr_;
        ptr_ = nullptr;
    };

    //copy operator and copy constructor deleted
    unique_ptr(const unique_ptr& second) = delete;
    unique_ptr& operator=(const unique_ptr& second) = delete;

    // move constructor and move operator implementation
    unique_ptr(unique_ptr&& second) noexcept { ptr_ = second.release(); }
    unique_ptr& operator=(unique_ptr&& second) noexcept {
        ptr_ = second.release();
        return *this;
    };

    // functions
    T* release() {
        T* ptrKeeper = get();  // keep pointer to return from function
        ptr_ = nullptr;
        return ptrKeeper;
    }

    T* get() noexcept { return ptr_; };  //access to raw pointer

    void reset(T* second) noexcept {
        delete ptr_;
        ptr_ = second;
    }

    void reset(unique_ptr&& second) noexcept {
        delete ptr_;
        ptr_ = second.release();
    }

    // operators overloading
    T& operator*() noexcept { return *get(); };
    T* operator->() const noexcept { return get(); };
};

}  // namespace pq