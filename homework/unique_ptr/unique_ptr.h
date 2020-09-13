#pragma once

namespace cs {

template <typename T>
class unique_ptr {
public:
    unique_ptr(T* ptr);
    unique_ptr(unique_ptr&& previousOwner);
    unique_ptr(const unique_ptr&) = delete;
    ~unique_ptr();

    T* release();
    const T* get() const;
    void reset(T* newPtr);

    T* operator->();
    T& operator*();

private:
    T* ptr_;
};

};  // namespace cs