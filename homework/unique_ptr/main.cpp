#include <iostream>

#include "PtrIsNullptr.hpp"
#include "unique_ptr.hpp"

int main() {
    unique_ptr<int> ptr(new int{10});

    std::cout << *ptr << '\n';

    int* ptr2 = ptr.get();
    std::cout << *ptr2 << '\n';

    unique_ptr<int> uptr;
    try {
        *uptr;
    } catch (const PtrIsNullptr& exc) {
        std::cout << exc.what() << '\n';
    }

    unique_ptr<int> ptr3(new int{10});
    unique_ptr<int> ptr4(new int{5});
    ptr3 = std::move(ptr4);

    return 0;
}
