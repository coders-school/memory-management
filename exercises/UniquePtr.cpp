#include <iostream>
#include <memory>
#include<typeinfo>

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
            UniquePtr(UniquePtr const&) = delete;
            UniquePtr& operator=(UniquePtr const&) = delete;

            T* operator->() const {return data;}
            T& operator*() const {return data;}

            T*get() const {return data;}
            explicit operator bool() const {return data;}

            T* relase()
            {
                T* result = nullptr;
                std::swap(result,data);
                return result;
            }

            void reset(T* data) noexcept(false)
            {
                delete data;
            }

};


int main ()
{
    return 0;
}