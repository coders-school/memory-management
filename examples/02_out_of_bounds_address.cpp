#include <iostream>

int main() {
    const auto size = 10;
    int* dynamicArray = new int[size];
    for (int i = 0; i <= size; ++i)
        *(dynamicArray + i) = i * 10;

    for (int i = 0; i <= size; ++i)
        std::cout << dynamicArray[i] << '\n';

    delete[] dynamicArray;
}
