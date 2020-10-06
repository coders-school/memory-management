#include <iostream>
#include "SharedPointer.hpp"
#include "WeakPointer.hpp"

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

    std::cout << "\n\nWeak pointers: \n";
    SharedPointer<int> s_ptr(new int(33));
    std::cout << "Shared counter = " << s_ptr.use_count() << "\n";
    WeakPointer<int> w_ptr(s_ptr);
    std::cout << "Shared counter = " << s_ptr.use_count() << "\n";
    std::cout << "Weak counter = " << w_ptr.use_count() << "\n";

    //w_ptr = s_ptr;
    auto sp = w_ptr.lock();
    if (!w_ptr.expired()) {
        std::cout << "sp = " << *sp << "\n";
    } else {
        std::cout << "Unable to lock \n";
    }

    std::cout << "Shared counter = " << s_ptr.use_count() << "\n";
    std::cout << "Weak counter = " << w_ptr.use_count() << "\n";

    w_ptr.reset();

    std::cout << "Shared counter = " << s_ptr.use_count() << "\n";
    std::cout << "Weak counter = " << w_ptr.use_count() << "\n";

    return 0;
}
