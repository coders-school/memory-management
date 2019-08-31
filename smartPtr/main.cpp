#include "smartPtr.hpp"
#include <iostream>
#include <assert.h>

struct A {
    A(int inputData) : member(inputData) { }  
    void foo() { std::cout << "The glorious integer: " << member << '\n'; }
    int member;
};

int main()
{
    smartPointer<int> smartPtr1(new int{5});
    assert(*smartPtr1==5);
    std::cout << "*smartPtr1: " << *smartPtr1 << '\n';

    smartPointer<int> smartPtr2(std::move(smartPtr1));
    assert(*smartPtr2==5);
    std::cout << "*smartPtr2: " << *smartPtr2 << '\n';
    
    int* regularPtr1 = smartPtr1.get();
    assert(regularPtr1==smartPtr1.get());
    assert(*regularPtr1==5);
    std::cout << "*(smartPtr1.get()): " << *(smartPtr1.get()) << '\n'
        << "*regularPtr1: " << *regularPtr1 << '\n'; 
        
    // copy not allowed
    // smartPtr1 = smartPtr2;

    smartPointer<A> smartPtr3(new A(7));
    assert(smartPtr3->member == 7);
    smartPtr3->foo(); 

    return 0;
}