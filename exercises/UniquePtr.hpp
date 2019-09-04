#pragma once

#include <memory>
#include <typeinfo>
#include <algorithm>

namespace UP {
template <typename T>
class UniquePtr {
  T* data;

    public:

        explicit UniquePtr(T* data)
            :data(data)
            {}
            ~UniquePtr(){
                delete data;
            }

            T* operator->() const {return data;}
            T& operator*() const {return *data;}

            T*get() const {return data;}

            T* relase()
            {
                T* result = nullptr;
                std::swap(result,data);
                return result;
            }

            void reset() noexcept(false)
            {
                T* data = relase();
                delete data;
            }



};
}