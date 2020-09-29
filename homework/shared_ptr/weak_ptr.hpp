#pragma once

#include "shared_ptr.hpp"

namespace cs {
template <typename T>
class weak_ptr {
public:
    constexpr weak_ptr() noexcept;
    weak_ptr( const weak_ptr& r ) noexcept;
    weak_ptr( const std::shared_ptr<T>& r ) noexcept;
    weak_ptr( weak_ptr<T>&& r ) noexcept;
    ~weak_ptr();

    weak_ptr& operator=( const weak_ptr<T>& r ) noexcept;
    weak_ptr& operator=( const shared_ptr<T>& r ) noexcept;
    weak_ptr& operator=( weak_ptr<T>&& r ) noexcept;

    void reset() noexcept;
    long use_count() const noexcept;
    bool expired() const noexcept;
    shared_ptr<T> lock() const noexcept;

};

} //namespace cs