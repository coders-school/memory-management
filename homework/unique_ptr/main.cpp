#include "uniquePTR.hpp"
#include <string>
#include <memory>
#include <iostream>


int main() {
    auto unique2 = unique_ptr<int>(new int (5));
    std::cout << *unique2;
    auto b = unique2.get();
    std::cout << *b;

} 