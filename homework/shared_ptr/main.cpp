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
    
    
    std::vector<SharedPtr<Scooter>> NewScooterVector;
    std::cout << "Vector size" << NewScooterVector.size();
    NewScooterVector.push_back(std::move(scooter));
    std::cout << "Vector size" << NewScooterVector.size() << '\n';
    //std::cout << "ShareCounter" << NewScooterVector.at(0).use_count()<< '\n';
    //std::cout << "scooter power" << scooter->power_<< '\n';
    //std::cout << "vector power" << NewScooterVector.at(0)->power_<< '\n';
    //std::cout << NewScooterVector.size();
    return 0;
}
