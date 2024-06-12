#include "unique_ptr.hpp"

int main() 
{
    // Create object
    unique_ptr<int> p1(new int(5));
    std::cout << *p1 << std::endl;
    
    // Move object
    unique_ptr<int> p2 = std::move(p1);
    if (p1.get() == nullptr) 
        std::cout << "p1 is null" << std::endl;

    std::cout << *p2 << std::endl;

    /* Reset */
    p2.reset(new int(10));
    std::cout << *p2 << std::endl;

    /* Release */
    int* rawPtr = p2.release();
    if (p2.get() == nullptr) 
        std::cout << "p2 is null" << std::endl;

    std::cout << *rawPtr << std::endl;
    delete rawPtr;

    return 0;
}