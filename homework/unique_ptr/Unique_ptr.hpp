#pragma once
#include <cstddef>

template <class Type>
class My_unique_ptr {
    public:
        
        My_unique_ptr(Type* value) : ptr_(value) {}

        My_unique_ptr(nullptr_t) : ptr_(nullptr) {}

        My_unique_ptr(const My_unique_ptr& other) noexcept = delete;

        My_unique_ptr(My_unique_ptr&& other) {
            ptr_ = other.release();
        }

        ~My_unique_ptr() noexcept {
            reset();
        }

        My_unique_ptr& operator=(const My_unique_ptr& other) noexcept = delete;

        My_unique_ptr& operator=(My_unique_ptr&& other) noexcept {
            if (other.ptr_ != ptr_) {
                delete ptr_;
                ptr_ = other.release();
            } 
            return *this;
        }

        My_unique_ptr& operator=(nullptr_t) noexcept {
            reset(nullptr);
            return *this;
        }

        explicit operator bool() noexcept {
            return ptr_;
        }

        Type& operator*() noexcept{
            return *ptr_;
        }

        const Type& operator*() const noexcept{
            return *ptr_;
        }


        Type* operator->() {
            return ptr_;
        }

        const Type* operator->() const noexcept {
            return ptr_;
        }

        Type* get() {
            return ptr_;
        }

        const Type* get() const {
            return ptr_;
        }


        Type* release() noexcept {
            auto temp = ptr_;
            ptr_ = nullptr;
            return temp;
        }

        void reset() {
            if (ptr_) {
                delete ptr_;
                ptr_ = nullptr;
            }
        }

        void reset(Type* newValue) {
            if (ptr_) {
                delete ptr_;
            }
            ptr_ = newValue;
            newValue = nullptr;
        }

    private:
        Type* ptr_;
};
