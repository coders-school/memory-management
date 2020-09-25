#include "md_unique_ptr.hpp"
#include "gtest/gtest.h"

class SomeUsefulClass { };

TEST(Test, dereferencingAfterGet)
{
   my_unique_ptr<int> ptr  = my_unique_ptr<int>(new int(10));
   EXPECT_EQ(*(ptr.get()), 10);
}
/*
TEST(Test, dereferencing)
{
   my_unique_ptr ptr  = my_unique_ptr<int>(nullptr);
   EXPECT_EQ(*ptr, 10);
}
*/
TEST(Test, emptyConstrustor)
{
   my_unique_ptr<int> ptr;
   my_unique_ptr<SomeUsefulClass> ptr_clas;
   EXPECT_EQ(*ptr, 0);
}

TEST(Test, ctrowithParam)
{

}
