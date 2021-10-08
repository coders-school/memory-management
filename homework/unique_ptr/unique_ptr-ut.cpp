#include <gtest/gtest.h>
#include "unique_ptr.hpp"

TEST(UniquePointerTest, ObjectInitialization) {
  
  //arrange
  ma::unique_ptr<int> ptr{new int{10}};

  //act

  //assert
  EXPECT_EQ(*ptr, 10);
}

TEST(UniquePointerTest, ObjectValueModification) {
  
  //arrange
  ma::unique_ptr<int> ptr{new int{10}};

  //act
  *ptr = 5;

  //assert
  EXPECT_EQ(*ptr, 5);
}

TEST(UniquePointerTest, MoveCtor) {
  
  //arrange
  ma::unique_ptr<int> ptr{new int{10}};

  //act
  auto ptr2 = std::move(ptr);

  //assert
  EXPECT_EQ(*ptr2, 10);
}

TEST(UniquePointerTest, MoveAssignmentOperator) {
  
  //arrange
  ma::unique_ptr<int> ptr{new int{10}};
  ma::unique_ptr<int> ptr2{new int{5}};
  //act
  ptr2 = std::move(ptr);

  //assert
  EXPECT_EQ(*ptr2, 10);
  EXPECT_EQ(ptr.get(), nullptr);
}

TEST(UniquePointerTest, PtrGet) {

  //arrange
  ma::unique_ptr<int> ptr{new int{10}};

  //act
  auto * ptr2 = ptr.get(); 

  //assert
 EXPECT_NE(ptr2, nullptr);
}

TEST(UniquePointerTest, PtrReset) {

  //arrange
  ma::unique_ptr<int> ptr{new int{10}};

  //act
  ptr.reset(new int{5}); 

  //assert
 EXPECT_EQ(*ptr, 5);
}

TEST(UniquePointerTest, PtrRelease) {

  //arrange
  ma::unique_ptr<int> ptr{new int{10}};

  //act
  auto * ptr2 = ptr.release(); 

  //assert
 EXPECT_EQ(*ptr2, 10);
 EXPECT_EQ(ptr.get(), nullptr);
}
