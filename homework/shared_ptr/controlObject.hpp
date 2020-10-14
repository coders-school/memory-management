#pragma once
#include "control.hpp"

namespace cs {
template <typename T>
class controlObject :public control_block<T> {
    T data_;
    public:
    controlObject(T data, Deleter<T> deleter = defaultDeleter);
    ~controlObject() = default;
    T* getObject() noexcept override;
};

template <typename T>
controlObject<T>::controlObject(T data, Deleter<T> deleter)
:control_block<T>(deleter), data_(data) {

}

template <typename T>
T* controlObject<T>::getObject() noexcept {
    return &data_;
}
};
