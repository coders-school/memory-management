#include "UniquePointer.hpp"

int main() {
    int number{5};
    UniquePointer<int> uniquePointer(int& number);

    return 0;
}
