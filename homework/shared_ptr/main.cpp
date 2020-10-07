#include <iostream>
#include <memory>
#include <utility>
#include "MakeShared.hpp"
#include "SharedPointer.hpp"

int main()
{
    std::cout << "Shared pointers: \n";
    SharedPointer<int> ptr2(new int(44));
    std::cout << *ptr2 << "\n";
    int* man_ptr = ptr2.get();
    std::cout << *man_ptr << "\n";
    std::cout << *ptr2.get() << "\n";
    std::cout << ptr2.use_count() << "\n";
    SharedPointer<int> ptr3(ptr2);
    *ptr3 += 5;

    SharedPointer<int> ptr4(ptr2);
    std::cout << ptr2.use_count() << "\n";

    std::cout << *ptr3.get() << "\n";
    std::cout << *ptr2.get() << "\n";
    std::cout << ptr3.use_count() << "\n";

    auto msPtr = MakeShared<int>(20);
    std::cout << *msPtr << "\n";
    std::cout << *msPtr.get() << "\n";
    std::cout << msPtr.use_count() << "\n";
    SharedPointer<int> ptr5 = msPtr;
    std::cout << msPtr.use_count() << "\n";
    {
        SharedPointer<int> ptr = msPtr;
        std::cout << msPtr.use_count() << "\n";
    }
    std::cout << msPtr.use_count() << "\n";

    return 0;
}
