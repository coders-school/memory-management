#pragma once

#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

class DereferenceNullPtr : public std::runtime_error {
public:
    DereferenceNullPtr(std::string error)
        : std::runtime_error(error) {}
};

// Base template

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
    T& operator*();
    T* get() const;
    T* release();
    void reset();
    void reset(T* pointer);

    template <typename MUType, typename... Args>
    friend UniquePointer<MUType> MakeUnique(Args&&...);

private:
    T* pointer_{};
};

// Implementation Base

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
    }
    pointer_ = anotherUniquePointerToMove.pointer_;
    anotherUniquePointerToMove.pointer_ = nullptr;
}

template <class T>
UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer&& anotherUniquePointerToMoveAssign)
{
    if (pointer_ != nullptr) {
        delete pointer_;
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
T& UniquePointer<T>::operator*()
{
    if (!pointer_) {
        throw DereferenceNullPtr(std::string("Dereference null pointer\n"));
    }
    return *pointer_;
}

template <class T>
T* UniquePointer<T>::operator->()
{
    if (!pointer_) {
        throw DereferenceNullPtr(std::string("Dereference null pointer\n"));
    }
    return pointer_;
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
T* UniquePointer<T>::release()
{
    T* temp = pointer_;
    pointer_ = nullptr;
    return temp;
}

//Array Specialization

template <class T>
class UniquePointer<T[]> {
public:
    UniquePointer(T* pointer = nullptr);
    UniquePointer(UniquePointer& anotherUniquePointerToCopy) = delete;
    UniquePointer(UniquePointer&& anotherUniquePointerToMove);
    UniquePointer<T[]>& operator=(UniquePointer& anotherUniquePointerToAssign) = delete;
    UniquePointer<T[]>& operator=(UniquePointer&& anotherUniquePointerToMoveAssing);
    T& operator[](int arrayElement);
    ~UniquePointer();
    T* operator->();
    T& operator*();
    T* get() const;
    T* release();
    void reset();
    void reset(T* pointer);

    template <typename MUType>
    friend UniquePointer<MUType> MakeUnique(unsigned);

private:
    T* pointer_{};
};

// Implementation Arrays

template <class T>
UniquePointer<T[]>::UniquePointer(T* pointer)
    : pointer_(pointer)
{
}

template <class T>
UniquePointer<T[]>::UniquePointer(UniquePointer&& anotherUniquePointerToMove)
{
    if (pointer_ != nullptr) {
        delete[] pointer_;
    }
    pointer_ = anotherUniquePointerToMove.pointer_;
    anotherUniquePointerToMove.pointer_ = nullptr;
}

template <class T>
UniquePointer<T[]>& UniquePointer<T[]>::operator=(UniquePointer&& anotherUniquePointerToMoveAssign)
{
    if (pointer_ != nullptr) {
        delete[] pointer_;
    }
    pointer_ = anotherUniquePointerToMoveAssign.pointer_;
    anotherUniquePointerToMoveAssign.pointer_ = nullptr;
    return *this;
}

template <class T>
T& UniquePointer<T[]>::operator[](int arrayElement)
{
    if (!pointer_) {
        throw DereferenceNullPtr(std::string("Dereference null pointer\n"));
    }
    return *(pointer_ + arrayElement);
}

template <class T>
UniquePointer<T[]>::~UniquePointer()
{
    delete[] pointer_;
    pointer_ = nullptr;
}

template <class T>
T& UniquePointer<T[]>::operator*()
{
    if (!pointer_) {
        throw DereferenceNullPtr(std::string("Dereference null pointer\n"));
    }
    return *pointer_;
}

template <class T>
T* UniquePointer<T[]>::operator->()
{
    if (!pointer_) {
        throw DereferenceNullPtr(std::string("Dereference null pointer\n"));
    }
    return pointer_;
}

template <class T>
void UniquePointer<T[]>::reset(T* pointer)
{
    if (pointer_ != nullptr) {
        delete[] pointer_;
        pointer_ = nullptr;
    }
    pointer_ = pointer;
}

template <class T>
void UniquePointer<T[]>::reset()
{
    if (pointer_ != nullptr) {
        delete[] pointer_;
        pointer_ = nullptr;
    }
}

template <class T>
T* UniquePointer<T[]>::get() const
{
    return pointer_;
}

template <class T>
T* UniquePointer<T[]>::release()
{
    T* temp = pointer_;
    pointer_ = nullptr;
    return temp;
}

//Make Unique

template <typename MUType>
using noArray = std::enable_if_t<!std::is_array_v<MUType>>;

template <typename MUType, typename... Args, typename = noArray<MUType>>
auto MakeUnique(Args&&... args)
{
    return UniquePointer<MUType>(new MUType(std::forward<Args>(args)...));
}

template <typename MUType>
auto MakeUnique(unsigned arraySize)
{
    return UniquePointer<MUType>(new typename std::remove_extent<MUType>::type[arraySize]());
}
