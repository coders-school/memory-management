#include <iostream>
#include "UniquePtr.hpp"

int main() {
    UniquePtr<int> intPtr(new int);
    *intPtr = 23;
    int* ptr = intPtr.release();
    try {
        *intPtr = 2;
    } catch (NullptrException& e) {
        std::cout << e.what() << '\n';
    }

    delete ptr;
}
