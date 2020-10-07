#include <string>
#include <iostream>
#include "my_shared_ptr.hpp"
#include "gtest/gtest.h"

struct SomeUsefulClass
{
    SomeUsefulClass() : message_(""){};
    SomeUsefulClass(std::string message) : message_(message){};
    std::string message_;
};

std::string functionUptrAsArg(my_shared_ptr<SomeUsefulClass> ptr)
{
    return ptr->message_;
}

my_shared_ptr<SomeUsefulClass> provider(std::string someString)
{
    return my_shared_ptr<SomeUsefulClass>(new SomeUsefulClass(someString));
}

TEST(Test, empty)
{
    my_shared_ptr<SomeUsefulClass> ptr = my_shared_ptr<SomeUsefulClass>();
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(Test, passedAsTemporary)
{
    std::string msg("some important message");
    EXPECT_EQ(msg, functionUptrAsArg(provider(msg)));
}

TEST(Test, passedResetOwneship)
{

    std::string msg("some important message");
    EXPECT_EQ(msg, functionUptrAsArg(provider(msg)));
}

TEST(Test, passedWithMove)
{
    std::string someString("provided by provider");
    my_shared_ptr<SomeUsefulClass> ptr = provider(someString);
    EXPECT_EQ(functionUptrAsArg(std::move(ptr)), someString);
}

TEST(Test, ShouldRelease)
{
    int initial_value = 42;
    int new_value = 100;

    my_shared_ptr<int> pointer_ = my_shared_ptr<int>(new int(initial_value));

    int* raw_pointer = &new_value;

    EXPECT_EQ(*(pointer_.get()), initial_value);

    raw_pointer = pointer_.release();

    EXPECT_EQ(pointer_.get(), nullptr);
    EXPECT_EQ(*raw_pointer, 42);

    delete raw_pointer;
}

TEST(Test, ShouldReset)
{
    int initial_value = 42;
    int another_initial_value = 43;

    my_shared_ptr<int> pointer_ = my_shared_ptr<int>(new int(initial_value));
    pointer_.reset(new int(another_initial_value));

    EXPECT_EQ(*(pointer_.get()), another_initial_value);
}

TEST(Test, emptyDefaultCtor)
{
    my_shared_ptr<SomeUsefulClass> ptr = my_shared_ptr<SomeUsefulClass>(new SomeUsefulClass());
    EXPECT_EQ(ptr->message_, "");
}

TEST(Test, dereferencingAfterGet)
{
    my_shared_ptr<int> ptr = my_shared_ptr<int>(new int(10));
    EXPECT_EQ(*(ptr.get()), 10);
}

/*
TEST(Test, deletedAsgnOperator_shouldNotCompile_withUseOfDeletedFunction)
{
    my_shared_ptr<int> ptr  = my_shared_ptr<int>(new int(10));
    my_shared_ptr<int> copy_ptr = ptr;
}
*/

/*

TEST(Test, deletedCopyConstructor_shouldNotCompile_withDeletedMethodError)
{
    my_shared_ptr<int> ptr  = my_shared_ptr<int>(new int(10));
    my_shared_ptr<int> copy_ptr = my_shared_ptr<int>(ptr);
}
*/
