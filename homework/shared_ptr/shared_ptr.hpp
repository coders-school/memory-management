#pragma once

namespace my {
template <class T>
class shared_ptr {
private:
    T* ptr_ = nullptr;
    size_t* counter_ = nullptr;

public:
    shared_ptr()
        : ptr_(nullptr), counter_(new size_t{0}) {}
    shared_ptr(T* ptr)
        : ptr_(ptr), counter_(new size_t{1}) {}
    shared_ptr(const shared_ptr& obj)
        : ptr_(obj.ptr_), counter_(obj.counter_) {
        if (obj.ptr_) {
            (*counter_)++;
        }
    }
    shared_ptr(shared_ptr&& obj)
        : ptr_(obj.ptr_), counter_(obj.counter_) {
        obj.ptr_ = nullptr;
        obj.counter_ = nullptr;
    }
    shared_ptr& operator=(const shared_ptr& obj) {
        if (this != &obj) {
            if (ptr_ != obj.ptr_) {
                deleter();
                ptr_ = obj.ptr_;
                counter_ = obj.counter_;
                if (obj.ptr_) {
                    (*counter_)++;
                }
            }
        }
        return *this;
    }
    shared_ptr& operator=(shared_ptr&& obj) {
        if (this != &obj) {
            deleter();
            ptr_ = obj.ptr_;
            counter_ = obj.counter_;
            obj.ptr_ = nullptr;
            obj.counter_ = nullptr;
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
        if (*(counter_)) {
            (*counter_)--;
        }
    }
    void reset() {
        if (ptr_) {
            delete ptr_;
            ptr_ = nullptr;
            if (counter_) {
                if (*(counter_)) {
                    (*counter_)--;
                }
            }
        }
    }
    long use_count() const {
        return *counter_;
    }
    ~shared_ptr() {
        deleter();
    }

private:
    void deleter() {
        if (counter_) {
            if (*(counter_) != 0) {
                (*counter_)--;
            }
            if ((*counter_) == 0) {
                if (ptr_) {
                    delete ptr_;
                    ptr_ = nullptr;
                }
                delete counter_;
                counter_ = nullptr;
            }
        }
    }
};
}  // namespace my
