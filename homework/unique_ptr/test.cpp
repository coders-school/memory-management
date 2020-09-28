#include <string>
#include <iostream>
#include "md_unique_ptr.hpp"
#include "gtest/gtest.h"

struct SomeUsefulClass {
    SomeUsefulClass() :str("") {
        std::cout << "default ctro called" << "\n";
    };
    std::string str;

};

TEST(Test, dereferencingAfterGet)
{
   my_unique_ptr<int> ptr  = my_unique_ptr<int>(new int(10));
   EXPECT_EQ(*(ptr.get()), 10);
}

TEST(Test, emptyDefaultCtor)
{
//   my_unique_ptr<SomeUsefulClass> ptr = my_unique_ptr<SomeUsefulClass>();
//   EXPECT_EQ(ptr, "");
}


TEST(Test, emptyCtorForClassAndDereferencing)
{
   my_unique_ptr<SomeUsefulClass> ptr;
   EXPECT_EQ((*ptr).str, "");
}

TEST(Test, emptyCtorForClassAndAccecViaPtr)
{
   my_unique_ptr<SomeUsefulClass> ptr;
   EXPECT_EQ(ptr->str, "");
}

TEST(Test, ctrowithParam)
{

}

/*

TEST(Test, dereferencing_shouldSegfault)
{
   my_unique_ptr ptr  = my_unique_ptr<int>(nullptr);
   EXPECT_EQ(*ptr, 10);
}


TEST(Test, deletedCopyConstructor_shouldNotCompile)
{
In member function ‘virtual void Test_deletedCopyConstructor_Test::TestBody()’:
error: use of deleted function ‘my_unique_ptr<T>::my_unique_ptr(const my_unique_ptr<T>&) [with T = int]’
my_unique_ptr<int> copy_ptr = ptr;

my_unique_ptr<int> ptr  = my_unique_ptr<int>(new int(10));
my_unique_ptr<int> copy_ptr = ptr;
EXPECT_EQ(*(ptr.get()), 10);
}
*/
