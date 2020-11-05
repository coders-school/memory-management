#pragma once
#include "control.hpp"

namespace cs {
template <typename ObjectType, typename... Args>
class controlObject :public control_block<ObjectType> {
    ObjectType data_{};
    public:
    controlObject(Args&&... dataArgs, Deleter<ObjectType> deleter = defaultDeleter);
    ~controlObject() = default;
    ObjectType* getObject() noexcept override;
};

template <typename ObjectType, typename... Args>
controlObject<ObjectType, Args...>::controlObject(Args&&... dataArgs, Deleter<ObjectType> deleter)
:control_block<ObjectType>{deleter},
 data_{dataArgs...} {

}

template <typename ObjectType, typename... Args>
ObjectType* controlObject<ObjectType, Args...>::getObject() noexcept {
    return &data_;
}
};
