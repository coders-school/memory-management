#pragma once

#include <utility>
#include "shared_ptr.hpp"

namespace my {

template <class T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    auto* buffer = new char[sizeof(T) + sizeof(typename shared_ptr<T>::control_block)];
    auto* data_ptr = new (buffer) T(std::forward<Args>(args)...);
    auto* control_ptr = new (buffer + sizeof(T)) typename shared_ptr<T>::control_block(true);
    return shared_ptr<T>(data_ptr, control_ptr);
}

}  // namespace my