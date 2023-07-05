#pragma once

#include "shared_ptr.hpp"

namespace my {
template <class Y>
class shared_ptr;
template <class T>
class weak_ptr {
private:
    T* ptr_ = nullptr;
    size_t* shared_refs_ = nullptr;
    size_t* weak_refs_ = nullptr;

public:
    constexpr weak_ptr()
        : ptr_(nullptr), weak_refs_(new size_t{0}) {}
    template <class Y>
    weak_ptr(const shared_ptr<Y>& obj)
        : ptr_(obj.ptr_), shared_refs_(obj.shared_refs_) {
        if (obj.ptr_) {
            weak_refs_ = new size_t{1};
        }
    }
    weak_ptr(const weak_ptr& obj)
        : ptr_(obj.ptr_), shared_refs_(obj.shared_refs_), weak_refs_(obj.weak_refs_) {
        if (obj.ptr_) {
            if (weak_refs_) {
                (*weak_refs_)++;
            }
        }
    }
    weak_ptr(weak_ptr&& obj)
        : ptr_(obj.ptr_), shared_refs_(obj.shared_refs_), weak_refs_(obj.weak_refs_) {
        obj.ptr_ = nullptr;
        obj.shared_refs_ = nullptr;
        obj.weak_refs_ = nullptr;
    }
    weak_ptr& operator=(const weak_ptr& obj) {
        if (this != &obj) {
            if (ptr_ != obj.ptr_) {
                deleter();
                ptr_ = obj.ptr_;
                weak_refs_ = obj.weak_refs_;
                shared_refs_ = obj.shared_refs_;
                if (obj.ptr_) {
                    (*weak_refs_)++;
                }
            }
        }
        return *this;
    }
    weak_ptr& operator=(weak_ptr&& obj) {
        if (this != &obj) {
            deleter();
            ptr_ = obj.ptr_;
            shared_refs_ = obj.shared_refs_;
            weak_refs_ = obj.weak_refs_;
            obj.ptr_ = nullptr;
            obj.shared_refs_ = nullptr;
            obj.weak_refs_ = nullptr;
        }
        return *this;
    }
    shared_ptr<T> lock() const {
        return expired() ? shared_ptr<T>(*this) : shared_ptr<T>();
    }
    long use_count() const {
        if (weak_refs_) {
            return *(weak_refs_);
        }
        return 0;
    }
    void reset() {
        *(weak_refs_) = 0;
    }
    bool expired() const {
        if (ptr_) {
            return true;
        }
        return false;
    }
    ~weak_ptr() {
        deleter();
    }

private:
    void deleter() {
        if (weak_refs_) {
            if (*(weak_refs_) != 0) {
                (*weak_refs_)--;
            }
            if (*(weak_refs_) == 0) {
                delete weak_refs_;
                weak_refs_ = nullptr;
            }
        }
    }
    template <class Y>
    friend class shared_ptr;
};
}  // namespace my
