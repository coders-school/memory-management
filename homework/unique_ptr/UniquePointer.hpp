#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <type_traits>

class DereferenceNullPtr : public std::runtime_error {
public:
    DereferenceNullPtr(std::string error)
        : std::runtime_error(error) {}
};

template <class T>
class UniquePointer {
public:
    UniquePointer(T* pointer = nullptr);
    UniquePointer(UniquePointer& anotherUniquePointerToCopy) = delete;
    UniquePointer(UniquePointer&& anotherUniquePointerToMove);
    UniquePointer<T>& operator=(UniquePointer& anotherUniquePointerToAssign) = delete;
    UniquePointer<T>& operator=(UniquePointer&& anotherUniquePointerToMoveAssing);
    ~UniquePointer();
    T* operator->();
    T operator*();
    T* get() const;
    T* replace();
    void reset();
    void reset(T* pointer);

private:
    T* pointer_{};
};

template <class T>
UniquePointer<T>::UniquePointer(T* pointer)
    : pointer_(pointer)
{
}

template <class T>
UniquePointer<T>::UniquePointer(UniquePointer&& anotherUniquePointerToMove)
{
    if (pointer_ != nullptr) {
        delete pointer_;
        pointer_ = nullptr;
    }
    pointer_ = anotherUniquePointerToMove.pointer_;
    anotherUniquePointerToMove.pointer_ = nullptr;
}

template <class T>
UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer&& anotherUniquePointerToMoveAssign)
{
    if (pointer_ != nullptr) {
        delete pointer_;
        pointer_ = nullptr;
    }
    pointer_ = anotherUniquePointerToMoveAssign.pointer_;
    anotherUniquePointerToMoveAssign.pointer_ = nullptr;
    return *this;
}

template <class T>
UniquePointer<T>::~UniquePointer()
{
    delete pointer_;
    pointer_ = nullptr;
}

template <class T>
T UniquePointer<T>::operator*()
{
    if (!pointer_) {
        throw DereferenceNullPtr(std::string("Dereference null pointer\n"));
    }
    return *pointer_;
}

template <class T>
T* UniquePointer<T>::operator->()
{
    if (pointer_ != nullptr) {
        return pointer_;
    }
    else {
        throw DereferenceNullPtr(std::string("Dereference null pointer\n"));
    }
}

template <class T>
void UniquePointer<T>::reset(T* pointer)
{
    if (pointer_ != nullptr) {
        delete pointer_;
        pointer_ = nullptr;
    }
    pointer_ = pointer;
}

template <class T>
void UniquePointer<T>::reset()
{
    if (pointer_ != nullptr) {
        delete pointer_;
        pointer_ = nullptr;
    }
}

template <class T>
T* UniquePointer<T>::get() const
{
    return pointer_;
}

template <class T>
T* UniquePointer<T>::replace()
{
    T* temp = pointer_;
    pointer_ = nullptr;
    return temp;
}