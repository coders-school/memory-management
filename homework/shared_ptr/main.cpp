#include <iostream>

#include "shared_ptr.hpp"
#include "weak_ptr.hpp"



int main()
{
  cs::shared_ptr<int> someInt(new int{42});
  auto makeSomeInt = cs::make_shared<int>(42);
  return 0;
}
