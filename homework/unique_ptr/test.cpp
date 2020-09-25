#include "md_unique_ptr.hpp"
#include "gtest/gtest.h"



TEST(Test, uniquePtrIncrement)
{
   my_unique_ptr ptr  = my_unique_ptr<int>(new int(10));
   EXPECT_EQ(*ptr, 10);
}

