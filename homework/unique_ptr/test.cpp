
#include "gtest/gtest.h"
#include "pq_unique_ptr.hpp"
#include <type_traits>
#include <memory>
#include <vector>

static constexpr auto TestVariable=55; 

struct MainOperations : public ::testing::Test {
    pq::unique_ptr<int> TestSmartPtr = pq::unique_ptr<int>(new int(TestVariable));
};


TEST_F(MainOperations, ShouldReturnValueWhenDereference) 
{
ASSERT_EQ(*TestSmartPtr,TestVariable);
ASSERT_NE(*TestSmartPtr,TestVariable+1);
}

TEST_F(MainOperations, ShouldBeNonCopyableWhenAssign) 
{
    auto isCopyable = std::is_copy_assignable<decltype(TestSmartPtr)>::value;
    ASSERT_EQ(isCopyable,false);
}

TEST_F(MainOperations, ShouldBeNonCopyableWhenConstruct) 
{
    auto isCopyable = std::is_copy_constructible<decltype(TestSmartPtr)>::value;
    ASSERT_EQ(isCopyable,false);
}

TEST_F(MainOperations, ShouldBeMoveableWhenAssign) 
{
    auto isMoveable = std::is_move_assignable<decltype(TestSmartPtr)>::value;
    ASSERT_EQ(isMoveable,true);
}

TEST_F(MainOperations, ShouldBeMoveableWhenConstruct) 
{
    auto isMoveable = std::is_move_constructible<decltype(TestSmartPtr)>::value;
    ASSERT_EQ(isMoveable,true);
}

TEST_F(MainOperations, ShouldGetRawPointerAndDereference) 
{
    auto RawPointer = TestSmartPtr.get();
    ASSERT_EQ(*RawPointer,TestVariable);
    ASSERT_NE(*RawPointer,TestVariable+1);

}

TEST_F(MainOperations, ShouldResetPointerAndCreateNewPointerWithNewValueByNewOperator) 
{
    auto OldPointer = TestSmartPtr.get();
    TestSmartPtr.reset(new int(42));
    ASSERT_NE(OldPointer,TestSmartPtr.get());
    ASSERT_EQ(*TestSmartPtr,42);
}

TEST_F(MainOperations, ShouldResetPointerAndMovePointerFromSecondSmartPointer) 
{
    auto SecondSmartPointer = pq::unique_ptr<int>(new int(TestVariable+100));
    TestSmartPtr=std::move(SecondSmartPointer);
    ASSERT_EQ(*TestSmartPtr,155);
    ASSERT_EQ(SecondSmartPointer.get(),nullptr);
}

    







