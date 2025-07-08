#include "unique_ptr.hpp"

namespace my {

unique_ptr::unique_ptr(T* ptr){};

unique_ptr::~unique_ptr() {
    if (!ptr_) {
        delete ptr_;
    }
};

unique_ptr::unique_ptr(unique_ptr&& other) {
    if (!ptr_) {
        delete ptr_;
    }
    T* ptr = other.release();
    ptr_ = ptr;
}

unique_ptr::unique_ptr& operator=(const unique_ptr& other) = delete;

unique_ptr& unique_ptr::operator=(unique_ptr&& other) {
    if (!ptr_) {
        delete ptr_;
    }
    T* ptr = other.release();
    ptr_ = ptr;
}

T& unique_ptr::operator*() {
    return *ptr_;
};

T* unique_ptr::operator->() {
    return ptr_;
};

T* unique_ptr::get() const { return ptr_ };

T* unique_ptr::release() {
    T* ptr = ptr_;
    ptr_ = nullptr;
    return ptr;
};

void unique_ptr::reset(T* ptr) {
    if (!ptr_) {
        delete ptr_;
    }
};

}  // namespace my