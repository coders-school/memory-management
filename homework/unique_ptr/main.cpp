#include <iostream>
#include "UniquePointer.hpp"

int main() {
    std::cout << "Unique pointers: \n";
    UniquePointer<int> ptr2(new int(44));
    std::cout << *ptr2 << "\n";
    std::cout << *ptr2.get() << "\n";
    auto pptr2 = ptr2.release();

    try {
        UniquePointer<int> uPtr(nullptr);
        ptr2 = std::move(uPtr);
        std::cout << *ptr2;
    } catch (NullPtrException& e) {
        std::cout << e.what() << '\n';
    }

    delete pptr2;

    UniquePointer<int> mptr{new int{14}};
    UniquePointer<int> mptr2 = std::move(mptr);
    UniquePointer<int> mptr3(std::move(mptr2));
    std::cout << *mptr3 << "\n";
    return 0;
}
