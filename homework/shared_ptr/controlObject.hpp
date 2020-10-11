#pragma once
#include "control.hpp"

namespace cs {
template <typename T>
class controlObject :public control_block<T> {
    T data_;
    public:
    controlObject(T data);
    ~controlObject();
    T* getObject() noexcept override;
};

template <typename T>
controlObject<T>::controlObject(T data)
:control_block<T>(), data_(data) {

}

template <typename T>
controlObject<T>::~controlObject() {
    delete data_;
}

template <typename T>
T* controlObject<T>::getObject() noexcept {
    return &data_;
}
};
