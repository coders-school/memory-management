#include "A.hpp"
#include "smartPtr.hpp"
#include <iostream>
#include <assert.h>

int main()
{
    smartPointer<int> smartPtr1(new int{5});
    assert(*smartPtr1==5);
    std::cout << "*smartPtr1: " << *smartPtr1 << '\n';

    smartPointer<int> smartPtr2(std::move(smartPtr1));
    assert(*smartPtr2==5);
    std::cout << "*smartPtr2: " << *smartPtr2 << '\n';
    
    int* regularPtr1 = smartPtr2.get();
    assert(regularPtr1==smartPtr2.get());
    assert(*regularPtr1==5);
    std::cout << "*(smartPtr2.get()): " << *(smartPtr2.get()) << '\n'
        << "*regularPtr1: " << *regularPtr1 << '\n'; 
        
    // copy not allowed
    // smartPtr1 = smartPtr2;

    smartPointer<A> smartPtr3(new A(7));
    assert(smartPtr3->member == 7);
    smartPtr3->foo(); 

    smartPointer<double> smartPtr4(new double(3.141));
    assert(*smartPtr4==3.141);
    smartPtr4.reset();
    assert(smartPtr4.get()==nullptr);

    smartPointer<int> smartPtr5(new int(5));
    assert(*smartPtr5==5);
    smartPtr5.reset(new int{6});
    assert(*smartPtr5==6);

    return 0;
}
