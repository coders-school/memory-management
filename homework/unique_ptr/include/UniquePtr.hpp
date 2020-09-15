#pragma once

template <typename T>
class UniquePtr {
public:
    UniquePtr(T* ptr)
        : p{ptr} {}

    UniquePtr(const UniquePtr&) = delete;

    ~UniquePtr() {
        delete p;
    }

    T operator*() const {
        return *p;
    }

    T* operator->() const {
        return p;
    }

    T* get() {
        if (p) {
            return p;
        }
        return nullptr;
    }

    T* release() {
        T* q = p;
        p = nullptr;
        return q;
    }

    void reset(T* ptr) {
        delete p;
        p = ptr;
    }

    // bool operator==(const UniquePtr<T>& ptr) {
    //     return this.get() == ptr.get();
    // }

private:
    T* p;
};
