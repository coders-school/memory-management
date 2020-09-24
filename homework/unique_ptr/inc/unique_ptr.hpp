#pragma once

namespace cs {
template <typename T>
class unique_ptr {
    bool isOwned{true};
    T* data_{nullptr};

   public:
    unique_ptr() = default;
    explicit unique_ptr(T* data) : data_(data){};
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& rhs) {
        delete data_;
        data_ = rhs.data_;
        rhs.data_ = nullptr;
    }
    unique_ptr& operator=(const unique_ptr&) = delete;
    unique_ptr& operator=(unique_ptr&& rhs) {
        if (isOwned) {
            delete data_;
        }
        data_ = rhs.data_;
        rhs.data_ = nullptr;
        isOwned = true;
        return *this;
    }
    T& operator*() const { return *data_; }
    T* operator->() const { return data_; }
    T* get() const {
        if (!isOwned) {
            return nullptr;
        }
        return data_;
    }
    T* release() {
        isOwned = false;
        return data_;
    }
    void reset(T* new_ptr = nullptr) {
        if (isOwned) {
            delete data_;
        }
        data_ = new_ptr;
        isOwned = true;
    }
    ~unique_ptr() {
        if (isOwned) {
            delete data_;
        }
    }
};
};  // namespace cs
