#include "Unique_ptr.hpp"
#include "Data.hpp"

#include <iostream>
#include <memory>
#include <string>

int main() {

    My_unique_ptr<Data> Tadzio(new Data(11, "January", 2016));
    Tadzio->print();
    My_unique_ptr<Data> Gucio1(new Data(30, "October", 2014));
    My_unique_ptr<Data> Gucio2 = std::move(Gucio1);
    Gucio2->print();
    if(!Gucio1) {
        std::cout << "Empty unique_ptr\n";
    }
    My_unique_ptr<Data> EmptyData(new Data(0, "", 0));
    EmptyData = std::move(Gucio2);
    EmptyData->print();
    if(!Gucio2) {
        std::cout << "Empty unique_ptr\n";
    }
    
    EmptyData = nullptr;
    if (!EmptyData) {
        std::cout << "again empty\n"; 
    }
    getchar();

    return 0;

}
