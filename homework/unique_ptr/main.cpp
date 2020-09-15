#include <iostream>
#include "UniquePtr.hpp"

int main() {
    UniquePtr<int> ptr{new int{5}};
    std::cout << *ptr << '\n';
    
    ptr.reset(new int{99});
    std::cout << *ptr << '\n';

    ptr.release();
    if (ptr.get() == nullptr) {
        std::cout << "It should be nullptr after ptr.release()!\n";
    }

    return 0;
}
