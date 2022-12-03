#pragma once

#include "shared_ptr.hpp"
// TODO: VERIFY
#include <type_traits>
#include <utility>

// TODO: VERIFY
//  #include <cstddef>

namespace my {

template <typename Type>
void deleteForMakeShared(Type* managedObj) {
    // TODO:
    if (!std::is_fundamental_v<Type>) {
        managedObj->~Type();
    }
    managedObj = nullptr;
    // delete managedObj;
    // managedObj = nullptr;
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

// TODO: make version for default construction;

// // TODO: VERIFY
// template <typename Type>
// struct ControllBlockWithObjectWrapper {
//     my::shared_ptr::ControlBlock;
//     T obj;
// };

// // TODO: VERIFY
// //  template <class T, class... Args>
// //  shared_ptr<T> make_shared(Args&&... args) {
// //      constexpr sizeToAlloc = sizeof(T) + sizeof(my::shared_ptr::ControlBlock);
// //      unsigned char buffer = new unsigned char[sizeToAlloc];
// //      my::shared_ptr::ControlBlock* ctrlBlockPtr = new (buffer) my::shared_ptr::ControlBlock(1, 0, deleteForMakeShared<T>);
// //      unsigned char* objectConstructionPosition = buffer + sizeof(my::shared_ptr::ControlBlock);

// template <class T, class... Args>
// shared_ptr<T> make_shared(Args&&... args) {
//     // TODO: VERIFY
//     //  constexpr sizeToAlloc = sizeof(T) + sizeof(my::shared_ptr::ControlBlock);
//     //  unsigned char buffer = new unsigned char[sizeToAlloc];
//     my::shared_ptr::ControlBlock* ctrlBlockPtr = new (buffer) my::shared_ptr::ControlBlock(1, 0, deleteForMakeShared<T>);
//     unsigned char* objectConstructionPosition = buffer + sizeof(my::shared_ptr::ControlBlock);
// }

// // // ------------------  OPTIONAL ---------------------------------

// // template <class T>
// // shared_ptr<T> make_shared(std::size_t N);  // NOTE:  OPTIONAL most likely

// // template <class T>
// // shared_ptr<T> make_shared();  // NOTE:  OPTIONAL most likely

// // template <class T>
// // shared_ptr<T> make_shared(std::size_t N, const std::remove_extent_t<T>& u);  // NOTE: OPTIONAL most likely

// // template <class T>
// // shared_ptr<T> make_shared(const std::remove_extent_t<T>& u);  // NOTE: OPTIONAL most likely

};  // namespace my
