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
    std::cout << "\n\tmy_pointer::unique_ptr<int> ptr2{new int{ptrValue}};\n";
    if (*ptr2.get() == ptrValue) {
        std::cout << "Constructor initialized with pointer owning value 5\n";
    }

    if (*ptr2 == ptrValue) {
        std::cout << "Value getting using dereference operator* value: *ptr==" << *ptr2 << "\n";
    }

    std::cout << "\n\tpointer operator bool()\n";
    if (!ptr) {
        std::cout << "ptr not own an object\n";
    }
    if (ptr2) {
        std::cout << "ptr2 own an object\n";
    }

    std::cout << "\n\tpointer function reset()\n";
    std::cout << "Before:\n";
    std::cout << "\tptr==nullptr\n";
    std::cout << "\tptr2==5\n";
    ptr.reset(new int{ptrValue});
    ptr2.reset();
    std::cout << "\tptr.reset(new int{5});\n";
    std::cout << "\tptr2.reset();\n";
    std::cout << "After:\n";
    if (ptr) {
        std::cout << "ptr own an object, value==" << *ptr << "\n";
    }
    if (!ptr2) {
        std::cout << "ptr2 not own an object\n";
    }

    std::cout << "\n\tpointer function release()\n";
    int* releasedPointer = ptr.release();
    if (!ptr) {
        std::cout << "Pointer ptr released, it own nothing\n";
    }
    if (releasedPointer) {
        std::cout << "raw pointer releasedPointer own value released from ptr, value==" << *releasedPointer << '\n';
    }
    delete releasedPointer;

    std::cout << "\n\tmove constructor\n";
    my_pointer::unique_ptr<int> ptr3 { new int { ptrValue } };
    auto ptrMoved { std::move(ptr3) };
    std::cout << "\tauto ptrMoved { std::move { ptr3 } };\n";
    if (!ptr3) {
        std::cout << "Pointer ptr3 transfered ownership to ptrMoved\n";
    }
    if (ptrMoved) {
        std::cout << "Pointer ptrMoved, value==" << *ptrMoved << '\n';
    }

    std::cout << "\n\tmove assigment\n";
    ptr3 = std::move(ptrMoved);
    std::cout << "\tgetting ptrMove back to ptr3\n";
    if (!ptrMoved) {
        std::cout << "Pointer ptrMoved transfered ownership to ptr3 using assingment operator=\n";
    }
    if (ptr3) {
        std::cout << "Pointer ptr3, value==" << *ptr3 << '\n';
    }

    return 0;
}
