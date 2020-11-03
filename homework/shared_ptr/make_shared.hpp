#pragma once

#include <utility>

#include "shared_ptr.hpp"

namespace cs {

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    return cs::shared_ptr<T>(new SharedControlBlockObj<T>(std::forward<Args>(args)...));
}

}  // namespace cs
