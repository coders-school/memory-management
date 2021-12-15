#include <iostream>

#include "UniquePtr.hpp"

constexpr int ptrValue = 5;

int main()
{
    std::cout << "Hello Pointer!\n";
    my_pointer::unique_ptr<int> ptr;
    std::cout << "\tmy_pointer::unique_ptr<int> ptr;\n";
    if (ptr.get() == nullptr) {
        std::cout << "Default constructor initialized pointer with nullptr value\n";
        std::cout << "Also get function return raw pointer to managed object\n";
    }

    my_pointer::unique_ptr<int> ptr2 { new int { ptrValue } };
    std::cout << "\tmy_pointer::unique_ptr<int> ptr2{new int{ptrValue}};\n";
    if (*ptr2.get() == 5) {
        std::cout << "Constructor initialized with pointer owning value 5\n";
    }

    return 0;
}
