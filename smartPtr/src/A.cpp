#include "A.hpp"
#include <iostream>

A::A(int inputData) : member(inputData) 
{ }  

void A::foo() 
{
    std::cout << "The glorious integer: " << member << '\n';
}

bool operator==(const A &a1, const A &a2)
{
    return a1.member == a2.member;
}

int A::bar(int input)
{
    return input*2;
}