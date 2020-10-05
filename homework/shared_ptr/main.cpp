#include "SharedPtr.hpp"
#include "Scooter.hpp"
#include <iostream>

int main(){

    int power{100};
    SharedPtr<Scooter> scooter(new Scooter(power));
    if(scooter){
        std::cout << "There is something inside";
    }
    SharedPtr<Scooter> scooter2{};
    if(scooter2){
        std::cout << "There is something inside";
    } else std::cout << "pointer is empty";
    return 0;
}
