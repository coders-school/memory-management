#pragma once

namespace cs {
template<typename T>
class unique_ptr {
    T* data_{nullptr};
    public:
    unique_ptr() = default;
    unique_ptr(T* data): data_(data) {};
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& rhs) {}
    unique_ptr& operator=(const unique_ptr&) = delete;
    unique_ptr& operator=(unique_ptr&& rhs) {
        
    }
    T& operator*() const {}
    T* operator->() const {}
    T* get() const {}
    T* release() {}
    void reset() {}
    ~unique_ptr() { delete data_; }
};
};  // namespace cs
