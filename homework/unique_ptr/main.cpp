
#include <iostream>
#include "pq_unique_ptr.hpp"
int main() 
{
auto w = pq::unique_ptr<char>(new char(55));

std::cout << "Hello World!" << *w << std::endl;

}
