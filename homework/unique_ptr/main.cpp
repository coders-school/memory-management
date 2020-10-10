#include "UniquePointer.hpp"

#include <iostream>
#include <vector>

int main()
{
    UniquePointer<int> uniquePtrToInt{new int{50}};
    std::cout << *uniquePtrToInt << "\n";

    UniquePointer<std::vector<int>> uniquePtrToVec{new std::vector<int>{50, 40, 50, 60, 10, 20}};
    for (auto el : *uniquePtrToVec) {
        std::cout << el << "\n";
    }

    return 0;
}