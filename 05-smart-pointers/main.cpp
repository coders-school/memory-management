#include <iostream>
#include <algorithm>
#include <string>
#include <array>
#include <cmath>
#include <map>
#include <memory>
#include <typeinfo>

#include "uniquePtrut.h"

namespace
{
template <typename T>
class UniquePtr;

template<typename T>
std::ostream& operator<< (std::ostream& os, UniquePtr<T>& ptr);

template <typename T>
class UniquePtr
{
    T* var = nullptr;
public:
    UniquePtr() {}
    explicit UniquePtr(T* var) : var(var) {}
    ~UniquePtr() { delete var; }
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& source)
    {
        var = source.var;
        source.var = nullptr;
    }

    UniquePtr<T>& operator=(const UniquePtr&& source)
    {
        if(this == &source)
            return *this;

        delete var;
        var = std::move(source.var);
        return this;
    }

    T get();
    void reset();
    T* release();

    friend std::ostream& operator<< <T>(std::ostream& os, UniquePtr<T>& ptr);
    T& operator();
    T operator->();
};

template <typename T>
void UniquePtr<T>::reset()
{
    delete var;
    var = nullptr;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, UniquePtr<T>& ptr)
{
    return os << ptr.var;
}

template<typename T>
T& UniquePtr<T>::operator*()
{
    return *var;
}

template<typename T>
T* UniquePtr<T>::operator->()
{
    return var;
}

template <typename T>
T* UniquePtr<T>::release()
{
    T* temp = nullptr;
    std::swap(temp, var);
    return temp;
}

template <typename T>
T* UniquePtr<T>::get()
{
    return var_;
}
}

int main()
{


    return 0;
}