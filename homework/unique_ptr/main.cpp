#include "UniquePointer.hpp"

#include <iostream>
#include <utility>
#include <vector>

int main()
{
    UniquePointer<int> uniquePtrToInt{new int{50}};
    std::cout << "uniquePtrToInt: " << *uniquePtrToInt << "\n";

    UniquePointer<std::vector<int>> uniquePtrToVec{new std::vector<int>{50, 40, 50, 60, 10, 20}};
    for (auto el : *uniquePtrToVec) {
        std::cout << el << "\n";
    }

    /* can't use copy constructor
    UniquePointer<int> uniquePtrToInt2 {uniquePtrToInt};
    std::cout << *uniquePtrToInt2 << "\n";
    */

    UniquePointer<int> uniquePtrToInt3 {std::move(uniquePtrToInt)};
    std::cout << "uniquePtrToInt3: " << *uniquePtrToInt3 << "\n";

    /* throw std::runtime_exception dereference null pointer, because std::move(uniquePtrToInt)
    std::cout << "up to int: " << *uniquePtrToInt << "\n"; 
    */

    /* can't use assigment operator 
    UniquePointer<int> uniquePtrToInt4;
    uniquePtrToInt4 = uniquePtrToInt3;
    */

    UniquePointer<int> uniquePtrToInt5;
    /* throw std::runtime_exception dereference null pointer, because std::move(uniquePtrToInt)
    std::cout << *uniquePtrToInt5 << "\n";
    */
    uniquePtrToInt5 = std::move(uniquePtrToInt3);
    std::cout << "uniquePtrToInt5: " << *uniquePtrToInt5 << "\n";
    /* throw std::runtime_exception dereference null pointer, because std::move(uniquePtrToInt)
    std::cout << *uniquePtrToInt3 << "\n";
    */
   
    return 0;
}