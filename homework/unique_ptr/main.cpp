#include "unique_ptr.hpp"
#include <iostream>

int main() {
    unique_ptr<int> uPtr(new int{10});
    std::cout << *uPtr;
    unique_ptr<int> uPtr2(std::move(uPtr));

    return 1;
}
