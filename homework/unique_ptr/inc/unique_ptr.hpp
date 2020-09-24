#pragma once

namespace cs {
template <typename T>
class unique_ptr {
    bool isReleased{false};
    T* data_{nullptr};

   public:
    unique_ptr() = default;
    unique_ptr(T* data) : data_(data){};
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& rhs) {
        delete data_;
        data_ = rhs.data_;
        rhs.data_ = nullptr;
    }
    unique_ptr& operator=(const unique_ptr&) = delete;
    unique_ptr& operator=(unique_ptr&& rhs) {
        delete data_;
        data_ = rhs.data_;
        rhs.data_ = nullptr;
    }
    T& operator*() const { return *data_; }
    T* operator->() const { return data_; }
    T* get() const { return data_; }
    T* release() {
        isReleased = true;
        return data_;
    }
    void reset(T* new_ptr = nullptr) {
        delete data_;
        data_ = new_ptr;
        isReleased = false;
    }
    ~unique_ptr() {
        if (!isReleased) {
            delete data_;
        }
    }
};
};  // namespace cs
