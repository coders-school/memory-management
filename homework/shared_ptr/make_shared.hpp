#pragma once

#include <type_traits>
#include <utility>
#include "shared_ptr.hpp"

namespace my {

template <typename Type>
void deleteForMakeShared(Type* managedObj) {
    if (!std::is_fundamental_v<Type>) {
        managedObj->~Type();
    }
    managedObj = nullptr;
}

template <typename Type>
class shared_ptr;

template <class Type, class... Args>
shared_ptr<Type> make_shared(Args&&... args) {
    constexpr auto controlBlockSize = sizeof(typename my::shared_ptr<Type>::ControlBlock);
    constexpr auto sizeToAlloc = sizeof(Type) + controlBlockSize;
    char* allocatedStorage = new char[sizeToAlloc];

    auto* createdObject = new (allocatedStorage) Type(std::forward<Args>(args)...);
    auto* controlBlock = new (allocatedStorage + sizeof(Type))
        my::shared_ptr<Type>::ControlBlock(1,
                                           0,
                                           deleteForMakeShared<Type>,
                                           allocatedStorage);

    my::shared_ptr<Type> result;
    result.ctrlBlock_ = controlBlock;
    result.ptr_ = createdObject;

    return result;
}

};  // namespace my
