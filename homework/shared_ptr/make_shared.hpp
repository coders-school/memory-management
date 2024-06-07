#pragma once
#include <memory>
#include <utility>
#include "SharedPtr.hpp"

namespace cs {
template <typename M, typename... Args>
cs::SharedPtr<M> makeShared(Args&&... args) {
    return cs::SharedPtr<M>(new SharedControlBlockData<M>(std::forward<decltype(args)>(args)...));
}
}  // namespace cs