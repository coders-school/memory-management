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

    smartPointer<int> smartPtr11(new int(11));
    smartPointer<int> smartPtr12(new int(12));
    smartPointer<int> smartPtr13(new int(13));
    smartPointer<int> smartPtr14(new int(14));

    std::cout << "*(smartPtr11.get()) before reset: " << *(smartPtr11.get()) << '\n';
    smartPtr11.reset();
    std::cout << "*(smartPtr11.get()) after reset: " << *(smartPtr11.get()) << '\n';

    std::cout << "*(smartPtr13.get()) before: " << *(smartPtr13.get()) << '\n';
    smartPtr13.reset(new int(113));
    std::cout << "*(smartPtr13.get()) after reset: " << *(smartPtr13.get()) << '\n';

    return 0;
}
