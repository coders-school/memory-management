#include <iostream>
#include <memory>
#include <typeinfo>
#include <algorithm>

namespace UP{
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
}

int main ()
{
    UP::UniquePtr<int> up1(new int(5));
    UP::UniquePtr<int> up2(new int(6));
    //std::cout << up1 << '\n';
    up1 = std::move(up2);
    
    return 0;
}