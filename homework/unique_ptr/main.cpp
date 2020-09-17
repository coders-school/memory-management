#include "uniqueptr.hpp"
#include "TestClass.hpp"
#include <vector>
#include <iostream>



int main(){
TestClass a(2);
int* ptr;
unique_ptr<TestClass> firstUnique = (TestClass(2));
int gotInt = firstUnique.get().data_;
std::cout << gotInt;

}





