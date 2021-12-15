#include <iostream>

#include "UniquePtr.hpp"

int main()
{
    std::cout << "Hello Pointer!\n";
    my_pointer::unique_ptr<int> ptr;
    std::cout << "\tmy_pointer::unique_ptr<int> ptr;\n";
    if (ptr.get() == nullptr) {
        std::cout << "Default constructor initialized pointer with nullptr value\n";
        std::cout << "Also get function return raw pointer to managed object\n";
    }
    return 0;
}
