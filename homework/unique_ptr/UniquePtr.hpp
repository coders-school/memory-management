#pragma once

template <typename T>
class UniquePtr {
public:
    UniquePtr() = default;
    UniquePtr(T * ptr) : ptr_(ptr) {}
    UniquePtr(const UniquePtr<T> &) = delete;

private:
    T * ptr_ = nullptr;
};