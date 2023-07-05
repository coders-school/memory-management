#pragma once
#include "weak_ptr.hpp"

namespace my {
template <class Y>
class weak_ptr;
template <class T>
class shared_ptr {
protected:
    T* ptr_ = nullptr;
    size_t* shared_refs_ = nullptr;

public:
    shared_ptr()
        : ptr_(nullptr), shared_refs_(new size_t{0}) {}
    shared_ptr(T* ptr)
        : ptr_(ptr), shared_refs_(new size_t{1}) {}
    shared_ptr(const shared_ptr& obj)
        : ptr_(obj.ptr_), shared_refs_(obj.shared_refs_) {
        if (obj.ptr_) {
            (*shared_refs_)++;
        }
    }
    shared_ptr(shared_ptr&& obj)
        : ptr_(obj.ptr_), shared_refs_(obj.shared_refs_) {
        obj.ptr_ = nullptr;
        obj.shared_refs_ = nullptr;
    }
    shared_ptr(const weak_ptr<T>& obj)
        : ptr_(obj.ptr_), shared_refs_(obj.shared_refs_) {
        if (obj.ptr_) {
            if (obj.shared_refs_) {
                (*shared_refs_)++;
            } else {
                shared_refs_ = new size_t{1};
            }
        }
    }
    shared_ptr& operator=(const shared_ptr& obj) {
        if (this != &obj) {
            if (ptr_ != obj.ptr_) {
                deleter();
                ptr_ = obj.ptr_;
                shared_refs_ = obj.shared_refs_;
                if (obj.ptr_) {
                    (*shared_refs_)++;
                }
            }
        }
        return *this;
    }
    shared_ptr& operator=(shared_ptr&& obj) {
        if (this != &obj) {
            deleter();
            ptr_ = obj.ptr_;
            shared_refs_ = obj.shared_refs_;
            obj.ptr_ = nullptr;
            obj.shared_refs_ = nullptr;
        }
        return *this;
    }
    operator bool() const {
        if (ptr_) {
            return true;
        }
        return false;
    }
    T* operator->() const {
        return ptr_;
    }
    T& operator*() const {
        return *(ptr_);
    }
    T* get() const {
        return ptr_;
    }
    void reset(T* newPtr) {
        T* tempPtr = ptr_;
        ptr_ = newPtr;
        if (tempPtr != nullptr) {
            delete tempPtr;
            tempPtr = nullptr;
        }
        if (*(shared_refs_)) {
            (*shared_refs_)--;
        }
    }
    void reset() {
        if (ptr_) {
            delete ptr_;
            ptr_ = nullptr;
            if (shared_refs_) {
                if (*(shared_refs_)) {
                    (*shared_refs_)--;
                }
            }
        }
    }
    long use_count() const {
        return *shared_refs_;
    }
    ~shared_ptr() {
        deleter();
    }

private:
    void deleter() {
        if (shared_refs_) {
            if (*(shared_refs_) != 0) {
                (*shared_refs_)--;
            }
            if ((*shared_refs_) == 0) {
                if (ptr_) {
                    delete ptr_;
                    ptr_ = nullptr;
                }
                delete shared_refs_;
                shared_refs_ = nullptr;
            }
        }
    }
    template <class Y>
    friend class weak_ptr;
};
}  // namespace my
