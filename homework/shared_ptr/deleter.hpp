#pragma once 

#include <type_traits>


template<typename T>
class Deleter {
public:
    void operator()(T* ptr) const {
        static_assert(!std::is_void<T>::value,
                      "can't delete pointer of incomplite type");
        static_assert(sizeof<T> > 0,
                      "can't delete pointer of incomplite type");
    }

};