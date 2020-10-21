#include "TestingClass.hpp"
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

    UniquePointer<int> uniquePtrToInt3{std::move(uniquePtrToInt)};
    std::cout << "uniquePtrToInt3: " << *uniquePtrToInt3 << "\n";

    UniquePointer<int> uniquePtrToInt5;

    uniquePtrToInt5 = std::move(uniquePtrToInt3);
    std::cout << "uniquePtrToInt5: " << *uniquePtrToInt5 << "\n";

    uniquePtrToInt5.reset(new int{77});
    std::cout << "uniquePtrToInt5: " << *uniquePtrToInt5 << "\n";

    int* rawPtrToInt5 = uniquePtrToInt5.get();
    std::cout << "rawPtrToInt5: " << *rawPtrToInt5 << "\n";
    std::cout << "uniquePtrToInt5: " << *uniquePtrToInt5 << "\n";

    int* rawPtrToInt5release = uniquePtrToInt5.release();

    std::cout << "rawPtrToInt5release: " << *rawPtrToInt5release << "\n";
    delete rawPtrToInt5release;

    UniquePointer<TestingClass> uniquePtrToClass{new TestingClass(std::string("Testing class"))};
    std::cout << uniquePtrToClass->testingGetter() << "\n";

    return 0;
}