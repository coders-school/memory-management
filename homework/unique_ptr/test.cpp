#include "md_unique_ptr.hpp"
#include "gtest/gtest.h"



TEST(Test, dereferencingAfterGet)
{
   my_unique_ptr ptr  = my_unique_ptr<int>(new int(10));
   EXPECT_EQ(*(ptr.get()), 10);
}

TEST(Test, dereferencing)
{
   my_unique_ptr ptr  = my_unique_ptr<int>(new int(10));
   EXPECT_EQ(*ptr, 10);
}

