#include <iostream>

int main() {
    int staticArray[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < 6; ++i)
        std::cout << staticArray[i] << '\n';

    constexpr auto size = 10;
    int* dynamicArray = new int[size];
    for (int i = 0; i < size; ++i)
        *(dynamicArray + i) = i * 10;

    for (int i = 0; i < size; ++i)
        std::cout << dynamicArray[i] << '\n';

    delete[] dynamicArray;
}
