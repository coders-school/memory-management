#pragma once

template <typename T>
class UniquePtr {
public:
    UniquePtr() = default;
    UniquePtr(T * ptr) : ptr_(ptr) {}

private:
    T * ptr_ = nullptr;
};