#include "A.hpp"
#include <iostream>

A::A(int inputData) : member(inputData) 
{ }  

void A::foo() 
{
    std::cout << "The glorious integer: " << member << '\n';
}