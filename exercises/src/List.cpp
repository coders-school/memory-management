#include <iostream>
#include <memory>
#include "List.hpp"
using namespace std;


int main()
{
    List lista2;
    auto node4 = std::make_shared<Node>(4);
    auto node7 = std::make_shared<Node>(7);
    lista2.add_front(node4);
    lista2.add_front(std::make_shared<Node>(2));
    lista2.add_front(node7);
    lista2.add_front(std::make_shared<Node>(9));
    lista2.find_back(1);

    return 0;
}

