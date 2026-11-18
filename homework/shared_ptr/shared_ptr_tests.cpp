#include "gtest/gtest.h"
#include "shared_ptr.hpp"

template class my::shared_ptr<int>;

class PointerConstructor : public ::testing::Test
{
public:
    int *temp = new int(10);
    ~PointerConstructor()
    {
        if (temp)
            delete temp;
    }
   
};

TEST_F(PointerConstructor, One_shared_pointer_use_count_should_return_1)
{
    my::shared_ptr<int> cut(temp);
    EXPECT_EQ(1, cut.use_count());
}

TEST_F(PointerConstructor, Two_shared_pointers_use_count_should_return_2)
{
    my::shared_ptr<int> cut(temp);
    my::shared_ptr<int> cut2(temp);
    EXPECT_EQ(2, cut.use_count());
}

TEST_F(PointerConstructor, Destructor_removing_one_of_two_pointers_use_count_should_return_1)
{
    my::shared_ptr<int> cut(temp);
    {
        my::shared_ptr<int> cut2(temp);
    }
    EXPECT_EQ(1, cut.use_count());
}

