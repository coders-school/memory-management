#include <iostream>
#include "uniquePTR.hpp"
#include <string>
#include <memory>


int main() {

  //auto unique = std::make_unique<int>(5);
  auto unique2 = unique_ptr<int>(new int (5));
  unique_ptr<int> unique3 = unique_ptr<int>(new int (8));
  auto unique4(std::move(unique3));
  unique4 = std::move(unique4);
  unique4 = std::move(unique2);
  //std::cout << *unique4 << "\n";
  // unique2 = unique3;
} 