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

std::string functionSharedPtrAsArg(my_shared_ptr<SomeUsefulClass>& ptr)
{
    return ptr->message_;
}

std::string functionSharedPtrAsArg(my_shared_ptr<SomeUsefulClass>&& ptr)
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
    EXPECT_EQ(ptr.use_count(), 0);
}

TEST(Test, notEmpty)
{
    my_shared_ptr<SomeUsefulClass> ptr = my_shared_ptr<SomeUsefulClass>(new SomeUsefulClass());
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(ptr.use_count(), 1);
}

TEST(Test, moreReferences)
{
    my_shared_ptr<SomeUsefulClass> ptr = my_shared_ptr<SomeUsefulClass>(new SomeUsefulClass());
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(ptr.use_count(), 1);
    my_shared_ptr<SomeUsefulClass>& another_ptr = ptr;
    my_shared_ptr<SomeUsefulClass> yet_another_ptr(another_ptr);

    EXPECT_EQ(another_ptr->message_, "");
    EXPECT_EQ(ptr.use_count(), 2);
}

TEST(Test, passedAsTemporary)
{
    std::string msg("some important message");
    EXPECT_EQ(msg, functionSharedPtrAsArg(provider(msg)));
}

TEST(Test, passedWithMove)
{
    std::string someString("provided by provider");
    my_shared_ptr<SomeUsefulClass> ptr = provider(someString);
    EXPECT_EQ(functionSharedPtrAsArg(std::move(ptr)), someString);
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

TEST(Test, asgnOperator)
{
    my_shared_ptr<int> ptr = my_shared_ptr<int>(new int(10));
    my_shared_ptr<int> copy_ptr = ptr;
}

TEST(Test, CopyConstructor)
{
    my_shared_ptr<int> ptr = my_shared_ptr<int>(new int(10));
    ASSERT_TRUE(ptr);
    my_shared_ptr<int> copy_ptr = my_shared_ptr<int>(ptr);
    ASSERT_TRUE(copy_ptr);
}


TEST(Test, ShouldReset)
{
    int initial_value = 42;
    int another_initial_value = 43;

    my_shared_ptr<int> pointer_ = my_shared_ptr<int>(new int(initial_value));
    pointer_.reset(new int(another_initial_value));

    EXPECT_EQ(*(pointer_.get()), another_initial_value);

}


