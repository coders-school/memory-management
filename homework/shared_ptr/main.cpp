#include <iostream>

#include "shared_ptr.hpp"
#include "weak_ptr.hpp"



int main()
{
  cs::weak_ptr<int> w_ptr;
  {
    auto s_ptr = cs::shared_ptr<int>(new int{5});
    w_ptr = s_ptr;
    
  }
  w_ptr.expired();
  return 0;
}
