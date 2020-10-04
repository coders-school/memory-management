#include <iostream>
#include "SharedPointer.hpp"

int main() {
    std::cout << "Shared pointers: \n";
    SharedPointer<int> ptr2(new int(44));
    std::cout << *ptr2 << "\n";
    int* man_ptr = ptr2.get();
    std::cout << *man_ptr << "\n";
    std::cout << *ptr2.get() << "\n";
    std::cout << ptr2.use_count() << "\n";
    SharedPointer<int> ptr3(ptr2);
    {
        SharedPointer<int> ptr4(ptr2);
        std::cout << ptr2.use_count() << "\n";
    }
    *ptr3 += 5;
    std::cout << *ptr3.get() << "\n";
    std::cout << *ptr2.get() << "\n";
    std::cout << ptr3.use_count() << "\n";
    return 0;
}
