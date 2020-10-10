#include "UniquePointer.hpp"

#include <iostream>

int main(){

    UniquePointer<int> uniquePtr {new int {50}};
    std::cout << *uniquePtr << "\n";

    return 0;
}