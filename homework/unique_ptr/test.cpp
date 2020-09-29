#include <string>
#include <iostream>
#include "my_unique_ptr.hpp"
#include "gtest/gtest.h"

struct SomeUsefulClass
{
    SomeUsefulClass() : message_(""){};
    SomeUsefulClass(std::string message) : message_(message){};
    std::string message_;
};

void functionUptrAsArg(my_unique_ptr<SomeUsefulClass> ptr)
{
    std::cout << ptr->message_ << "\n";
}
/*
my_unique_ptr<SomeUsefulClass> provider(std::string someString)
{
    return my_unique_ptr<SomeUsefulClass>(someString); 
}
*/

TEST(Test, dereferencingAfterGet)
{
    my_unique_ptr<int> ptr = my_unique_ptr<int>(new int(10));
    EXPECT_EQ(*(ptr.get()), 10);
}

TEST(Test, emptyDefaultCtor)
{
       my_unique_ptr<SomeUsefulClass> ptr = my_unique_ptr<SomeUsefulClass>();
       EXPECT_EQ(ptr->message_, "");
}

TEST(Test, emptyCtorForClassAndDereferencing)
{
    my_unique_ptr<SomeUsefulClass> ptr;
    EXPECT_EQ((*ptr).message_, "");
}

TEST(Test, emptyCtorForClassAndAccecViaPtr)
{
    my_unique_ptr<SomeUsefulClass> ptr;
    EXPECT_EQ(ptr->message_, "");
}

TEST(Test, ctrowithParam)
{
}

/*

TEST(Test, deletedCopyConstructor_shouldNotCompile)
{
    my_unique_ptr<int> copy_ptr = ptr;

    my_unique_ptr<int> ptr  = my_unique_ptr<int>(new int(10));
    my_unique_ptr<int> copy_ptr = ptr;
    EXPECT_EQ(*(ptr.get()), 10);
}
*/
