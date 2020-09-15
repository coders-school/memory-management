#pragma once

class NullptrDereferenceError : public std::runtime_error {
public:
    NullptrDereferenceError()
        : std::runtime_error{"Cannot dereference nullptr"} {}
};

template <typename T>
class UniquePtr {
public:
    UniquePtr(T* ptr)
        : ptr_{ptr} {}

    UniquePtr(const UniquePtr<T>&) = delete;

    UniquePtr(UniquePtr<T>&& ptr)
        : ptr_{ptr.release()} {}

    UniquePtr<T>& operator=(const UniquePtr<T>&) = delete;
    UniquePtr<T>& operator=(UniquePtr<T>&& ptr) {
        if (!ptr_) {
            return *this;
        }
        delete ptr_;
        ptr_ = ptr.ptr_;
        ptr.ptr_ = nullptr;
        return *this;
    }

    T operator*() const {
        if (!ptr_) {
            throw NullptrDereferenceError();
        }
        return *ptr_;
    }

    T* operator->() const {
        return ptr_;
    }

    T* get() {
        if (ptr_) {
            return ptr_;
        }
        return nullptr;
    }

    T* release() {
        T* ptr = ptr_;
        delete ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    void reset(T* ptr) {
        if (ptr_) {
            delete ptr_;
        }
        ptr_ = ptr;
    }

    ~UniquePtr() {
        delete ptr_;
    }

private:
    T* ptr_;
};
