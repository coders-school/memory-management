#include "gtest/gtest.h"
#include "shared_ptr.hpp"

template class my::shared_ptr<int>;

class PointerConstructor : public ::testing::Test
{
public:
    int *temp = new int(10);   
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




class CopyConstructor : public ::testing::Test
{
public:
    int *temp = new int(10);
};

TEST_F(CopyConstructor, Two_shared_pointers_after_copy_one_to_another_use_count_for_first_should_return_2)
{
    my::shared_ptr<int> cut(temp);
    my::shared_ptr<int> cut2(cut);
    EXPECT_EQ(2, cut.use_count());
}

TEST_F(CopyConstructor, Two_shared_pointers_after_copy_one_to_another_use_count_for_second_should_return_2)
{
    my::shared_ptr<int> cut(temp);
    my::shared_ptr<int> cut2(cut);
    EXPECT_EQ(2, cut2.use_count());
}



class MoveConstructor : public ::testing::Test
{
public:
    int *temp = new int(10);
};

TEST_F(MoveConstructor, Two_shared_pointers_after_move_one_to_another_use_count_for_first_should_return_0)
{
    my::shared_ptr<int> cut(temp);
    my::shared_ptr<int> cut2(std::move(cut));
    EXPECT_EQ(0, cut.use_count());
}

TEST_F(MoveConstructor, Two_shared_pointers_after_move_one_to_another_use_count_for_second_should_return_1)
{
    my::shared_ptr<int> cut(temp);
    my::shared_ptr<int> cut2(std::move(cut));
    EXPECT_EQ(1, cut2.use_count());
}




class ReleaseMethod : public ::testing::Test
{};

TEST_F(ReleaseMethod, shared_ptr_use_count_should_return_zero)
{
    my::shared_ptr<int> cut(new int(12));
    int *ptr = cut.release();
    EXPECT_EQ(0, cut.use_count());
}

TEST_F(ReleaseMethod, shared_ptr_get_method_should_return_nullptr)
{
    my::shared_ptr<int> cut(new int(12));
    int *ptr = cut.release();
    EXPECT_EQ(nullptr, cut.get());
}

TEST_F(ReleaseMethod, ptr_should_return_previous_value_of_shared_ptr)
{
    my::shared_ptr<int> cut(new int(12));
    int *ptr = cut.release();
    EXPECT_EQ(12, *ptr);
}



class ResetMethod : public ::testing::Test
{
};

TEST_F(ResetMethod, shared_ptr_should_return_value_of_ptr)
{
    my::shared_ptr<int> cut(new int(12));
    int *ptr = new int(20);
    cut.reset(ptr);
    EXPECT_EQ(20, *cut.get());
}

TEST_F(ResetMethod, shared_ptr_use_count_should_return_1)
{
    my::shared_ptr<int> cut(new int(12));
    int *ptr = new int(20);
    cut.reset(ptr);
    EXPECT_EQ(1, cut.use_count());
}



class OperatorBool : public ::testing::Test
{
};

TEST_F(OperatorBool, shared_ptr_should_return_nullptr)
{
    my::shared_ptr<int> cut;

    EXPECT_FALSE(bool(cut));
}

TEST_F(OperatorBool, shared_ptr_should_return_non_nullptr)
{
    my::shared_ptr<int> cut(new int(12));

    EXPECT_TRUE(bool(cut));
}



class OperatorAsterisk : public ::testing::Test
{};

TEST_F(OperatorAsterisk, dereference_should_return_result_of_foo_get)
{
    struct foo
    {
        int get()
        {
            return 2;
        }
    };

    my::shared_ptr<foo> ptr;

    EXPECT_EQ(2, (*ptr).get());
}




class OperatorArrow : public ::testing::Test
{
};

TEST_F(OperatorArrow, arrow_should_return_result_of_foo_get)
{
    struct foo
    {
        int get()
        {
            return 2;
        }
    };

    my::shared_ptr<foo> ptr;

    EXPECT_EQ(2, ptr->get());
}



class AssignOperator : public ::testing::Test
{
};

TEST_F(AssignOperator, use_count_should_be_incremented_after_copying_value_returned_by_source)
{
    my::shared_ptr<int> ptr1 = (new int(12));
    my::shared_ptr<int> ptr2;
    ptr2 = ptr1;

    EXPECT_EQ(2, ptr1.use_count());
}

TEST_F(AssignOperator, use_count_should_be_incremented_after_copying_value_returned_by_destination)
{
    my::shared_ptr<int> ptr1 = (new int(12));
    my::shared_ptr<int> ptr2;
    ptr2 = ptr1;

    EXPECT_EQ(2, ptr2.use_count());
}

//class MoveConstructor : public ::testing::Test 
//{
//public:
//    int *temp = new int(10);
//};
//
//TEST_F(MoveConstructor, One_shared_pointer_use_count_should_return_1)
//{
//    my::shared_ptr<int> cut(new int(12));
//    EXPECT_EQ(1, cut.use_count());
//}
//
//TEST_F(MoveConstructor, Two_shared_pointers_use_count_should_return_2)
//{
//    my::shared_ptr<int> cut(std::move(temp));
//    my::shared_ptr<int> cut2(std::move(temp));
//    EXPECT_EQ(2, cut.use_count());
//}

//TEST_F(MoveConstructor, One_shared_pointer_use_count_should_return_1)
//{
//    my::shared_ptr<int> cut(new int(12));
//    EXPECT_EQ(1, cut.use_count());
//}
