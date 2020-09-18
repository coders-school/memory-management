#include "uniqueptr.hpp"
#include "TestClass.hpp"
#include <vector>
#include <iostream>



int main(){
unique_ptr<TestClass> firstUnique( new TestClass(2.0));
std::vector<unique_ptr<TestClass>> PtrShop;
PtrShop.push_back(std::move(firstUnique));
//PtrShop.push_back(firstUnique); // will not work, because copy constructor is deleted!
if(firstUnique.get() == nullptr){
std::cout << "We removed raw_ptr from unique_ptr!" <<'\n';
}
if(PtrShop.at(0).get() != nullptr){
int dataFromShop = PtrShop.at(0).get()->data_;
std::cout << "Now data from our unique ptr is in vector: " << dataFromShop << "!\n";
}
std::cout << "raw_ptr adress stored in vector's unique_ptr after std::move(): " << firstUnique.get() << '\n';
// std::cout << "Data stored in firstUnique: " << (*firstUnique).data_ << '\n'; // dereferencing nullptr!
firstUnique.reset(new TestClass(3.0));
std::cout << "Data stored in firstUnique: " << (*firstUnique).data_ << '\n';
}





