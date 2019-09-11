#include <gtest/gtest.h>
#include "../src/List.hpp"

using namespace ::testing;



struct ListTests : public testing::Test
{
    List list;
};

TEST_F(ListTests, canInsertNodeAtTheBeginningOfTheList)
{
    //Arrange
    list.add(std::make_shared<Node>(9));

    //Act
    list.add_front(std::make_shared<Node>(20));
    auto firstElementPtr = list.getFirst();
    int firstElementValue = firstElementPtr->value;
    //Assert
    ASSERT_EQ(20, firstElementValue);
}

TEST_F(ListTests, BackwardSearchingEmptyListShouldResultInNullptr)
{
    //Act
    auto result = list.find_back(5);

    //Assert
    ASSERT_EQ(nullptr, result);
}

TEST_F(ListTests, BackwardSearchingNotExistingElementShouldResultInNullptr)
{
    //Arrange
    list.add(std::make_shared<Node>(9));

    //Act
    auto result = list.find_back(5);

    //Assert
    ASSERT_EQ(nullptr, result);
}

TEST_F(ListTests, BackwardSearchingExistingElementReturnsPointerToNode)
{
    //Arrange
    list.add(std::make_shared<Node>(9));
    list.add_front(std::make_shared<Node>(10));

    //Act
    auto searchedElement = list.find_back(10);

    //Assert
    ASSERT_EQ(list.getFirst(), searchedElement);
}