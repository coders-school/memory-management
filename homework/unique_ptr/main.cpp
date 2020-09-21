#include <iostream>
#include "UniquePtr.hpp"

auto moveTest() {
    UniquePtr<int> ptr{new int{9}};
    return ptr;
}

int main() {
    UniquePtr<int> ptr{new int{5}};
    std::cout << *ptr << '\n';

    ptr.reset(new int{99});
    std::cout << *ptr << '\n';

    int* released = ptr.release();
    if (ptr.get() == nullptr) {
        std::cout << "It should be nullptr after ptr.release()!\n";
    }

    if (*released == 99) {
        std::cout << "Released pointer should have value of 99!\n";
    }
    delete released;

    UniquePtr<int> ptr2{moveTest()};
    std::cout << *ptr2 << '\n';

    UniquePtr<int> ptr3{new int{21}};
    std::cout << *ptr3 << '\n';
    ptr3 = moveTest();
    std::cout << *ptr3 << '\n';

    try {
        UniquePtr<int> ptr4{nullptr};
        std::cout << *ptr4 << '\n';

    } catch (const NullptrDereferenceError& err) {
        std::cerr << "Exception: " << err.what() << '\n';
    }

    return 0;
}
