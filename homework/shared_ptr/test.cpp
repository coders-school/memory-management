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

class SharedPointerTestSuite : public ::testing::Test {
public:
  SharedPointerTestSuite()
      : m_someString("provided by provider"),
        m_msg("some important message"),
        m_sut(provider(m_msg)) {}

  std::string m_someString;
  std::string m_msg;
  my_shared_ptr<SomeUsefulClass> m_sut;
  my_shared_ptr<SomeUsefulClass> m_sut_empty = my_shared_ptr<SomeUsefulClass>();

  int initial_value = 42;
  int new_value = 100;
};


TEST_F(SharedPointerTestSuite, notEmptySharedPtr)
{
    EXPECT_NE(m_sut.get(), nullptr);
    EXPECT_EQ(m_sut.use_count(), 1);
}

TEST_F(SharedPointerTestSuite, emptySharedPtr)
{
    EXPECT_EQ(m_sut_empty.get(), nullptr);
    EXPECT_EQ(m_sut_empty.use_count(), 0);
}

TEST_F(SharedPointerTestSuite, moreReferencesSharedPointerTestSuite)
{
    my_shared_ptr<SomeUsefulClass> ptr = my_shared_ptr<SomeUsefulClass>(new SomeUsefulClass());
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(ptr.use_count(), 1);
    my_shared_ptr<SomeUsefulClass>& another_ptr = ptr;
    EXPECT_EQ(ptr.use_count(), 1);  // ref does not create a copy
    
    my_shared_ptr<SomeUsefulClass> yet_another_ptr(another_ptr);
    EXPECT_EQ(another_ptr->message_, "");
    EXPECT_EQ(ptr.use_count(), 2);
}

TEST_F(SharedPointerTestSuite, passedAsTemporary)
{
    EXPECT_EQ(m_msg, functionSharedPtrAsArg(provider(m_msg)));
}

TEST_F(SharedPointerTestSuite, passedWithMove)
{
    EXPECT_EQ(m_msg, functionSharedPtrAsArg(std::move(m_sut)));
}

TEST_F(SharedPointerTestSuite, moveAssigmenOperator)
{
    my_shared_ptr<SomeUsefulClass> some_ptr = my_shared_ptr<SomeUsefulClass>(new SomeUsefulClass());;
    my_shared_ptr<SomeUsefulClass> another_ptr = my_shared_ptr<SomeUsefulClass>(new SomeUsefulClass());;
    another_ptr  = std::move(some_ptr);  // now we have move assignment

    EXPECT_EQ(another_ptr->message_, "");
    EXPECT_EQ(another_ptr.use_count(), 1);

    EXPECT_EQ(some_ptr.get(), nullptr);
    EXPECT_EQ(some_ptr.use_count(), 0);
    ASSERT_FALSE(some_ptr);
}

TEST_F(SharedPointerTestSuite, moveConstructor)
{
    my_shared_ptr<SomeUsefulClass> some_ptr = my_shared_ptr<SomeUsefulClass>(new SomeUsefulClass());;
    my_shared_ptr<SomeUsefulClass> another_ptr = my_shared_ptr<SomeUsefulClass>(std::move(some_ptr));;

    EXPECT_EQ(another_ptr->message_, "");
    EXPECT_EQ(another_ptr.use_count(), 1);

    EXPECT_EQ(some_ptr.get(), nullptr);
    EXPECT_EQ(some_ptr.use_count(), 0);
    ASSERT_FALSE(some_ptr);
}

TEST_F(SharedPointerTestSuite, dereferencingAfterGet)
{
    EXPECT_EQ( (*(m_sut.get())).message_, m_msg);
}

TEST_F(SharedPointerTestSuite, asgnOperator)
{
    auto copy_ptr = my_shared_ptr<SomeUsefulClass>(new SomeUsefulClass{});
    copy_ptr = m_sut;  // this calls copy assignment operator
    EXPECT_EQ(copy_ptr.use_count(), 2);
}

TEST_F(SharedPointerTestSuite, CopyConstructorAndBoolConversion)
{
    my_shared_ptr<int> ptr = my_shared_ptr<int>(new int(initial_value));
    ASSERT_TRUE(ptr);
    my_shared_ptr<int> copy_ptr = my_shared_ptr<int>(ptr);
    ASSERT_TRUE(copy_ptr);
}

TEST_F(SharedPointerTestSuite, ShouldReset)
{
    my_shared_ptr<int> pointer_ = my_shared_ptr<int>(new int(initial_value));
    pointer_.reset(new int(new_value));
    EXPECT_EQ(*pointer_, new_value);
}

TEST_F(SharedPointerTestSuite, ShouldResetWithSimpleClass)
{
    m_sut.reset(new SomeUsefulClass(m_someString));
    EXPECT_EQ((*m_sut.get()).message_, m_someString);
}

TEST_F(SharedPointerTestSuite, ShouldResetWithNullptr)
{
    m_sut.reset(nullptr);
    EXPECT_EQ(m_sut.get(), nullptr);
    EXPECT_EQ(m_sut.use_count(), 0);
}

TEST_F(SharedPointerTestSuite, ShouldResetWithoutArg)
{
    m_sut.reset();
    EXPECT_EQ(m_sut.get(), nullptr);
}
