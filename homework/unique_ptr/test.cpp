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

std::string functionUptrAsArg(my_unique_ptr<SomeUsefulClass> ptr)
{
    return ptr->message_;
}

my_unique_ptr<SomeUsefulClass> provider(std::string someString)
{
    return my_unique_ptr<SomeUsefulClass>(new SomeUsefulClass(someString));
}

class UniquePointerTestSuite : public ::testing::Test {
public:
  UniquePointerTestSuite()
      : m_someString("provided by provider"),
        m_msg("some important message"),
        m_sut(provider(m_msg)) {}

  std::string m_someString;
  std::string m_msg;
  my_unique_ptr<SomeUsefulClass> m_sut;

  int initial_value = 42;
  int new_value = 100;

};


TEST_F(UniquePointerTestSuite, passedAsTemporary)
{
    EXPECT_EQ(m_msg, functionUptrAsArg(provider(m_msg)));
}

TEST_F(UniquePointerTestSuite, passedWithMoveAndResetOwneship)
{
    EXPECT_EQ(m_msg, functionUptrAsArg(std::move(m_sut)));
    EXPECT_EQ(m_sut.get(), nullptr);
}

TEST_F(UniquePointerTestSuite, passedWithMove)
{
    my_unique_ptr<SomeUsefulClass> ptr = provider(m_someString);
    EXPECT_EQ(functionUptrAsArg(std::move(ptr)), m_someString);
}

TEST_F(UniquePointerTestSuite, moveOperator)
{
    my_unique_ptr<SomeUsefulClass> ptr2 = std::move(m_sut);
    EXPECT_EQ(m_sut.get(), nullptr);
    EXPECT_EQ(ptr2->message_,m_msg);
}

TEST_F(UniquePointerTestSuite, moveOperatorTestWithCast)
{
    my_unique_ptr<SomeUsefulClass> ptr2 = std::move(m_sut);
    EXPECT_EQ(m_sut.get(), nullptr);
    EXPECT_EQ(ptr2->message_,m_msg);
}

TEST_F(UniquePointerTestSuite, ShouldRelease)
{
    my_unique_ptr<int> pointer_ = my_unique_ptr<int>(new int(initial_value));

    int* raw_pointer = &new_value;

    EXPECT_EQ(*(pointer_.get()), initial_value);

    raw_pointer = pointer_.release();

    EXPECT_EQ(pointer_.get(), nullptr);
    EXPECT_EQ(*raw_pointer, initial_value);

    delete raw_pointer;
}

TEST_F(UniquePointerTestSuite, ShouldReset)
{
    my_unique_ptr<int> pointer_ = my_unique_ptr<int>(new int(initial_value));
    pointer_.reset(new int(new_value));

    EXPECT_EQ(*(pointer_.get()), new_value);
}

TEST_F(UniquePointerTestSuite, ShouldResetWhenEmpty)
{
    my_unique_ptr<int> pointer_ = my_unique_ptr<int>(new int(initial_value));
    pointer_.reset();

    EXPECT_EQ(pointer_.get(), nullptr);
}

TEST_F(UniquePointerTestSuite, emptyDefaultCtor)
{
    my_unique_ptr<SomeUsefulClass> ptr = my_unique_ptr<SomeUsefulClass>(new SomeUsefulClass());
    EXPECT_EQ(ptr->message_, "");
}

TEST_F(UniquePointerTestSuite, dereferencingAfterGet)
{
    my_unique_ptr<int> ptr = my_unique_ptr<int>(new int(initial_value));
    EXPECT_EQ(*(ptr.get()), initial_value);
}
