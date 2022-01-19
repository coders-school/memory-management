#include "unique_ptr.hpp"
#include "gtest/gtest.h"

#include <vector>

constexpr int ptrValue = 123;
constexpr int ptrValueRef = 456;

struct ClassUnderTestFixture : public ::testing::Test {

    int* wsk = new int(ptrValue);
    Unique<int> ptr{ wsk };
};

TEST_F(ClassUnderTestFixture, CreateNullPtr)
{

    Unique<int> ptrNull{};

    EXPECT_EQ(ptrNull.get(), nullptr);
    EXPECT_THROW(*ptrNull, std::runtime_error);
}

TEST_F(ClassUnderTestFixture, CreateUniquePtr)
{

    EXPECT_EQ(*ptr, ptrValue);
    EXPECT_EQ(ptr.get(), wsk);
}

TEST_F(ClassUnderTestFixture, ResetUniquePtr)
{

    ptr.reset(nullptr);
    EXPECT_EQ(ptr.get(), nullptr);

    ptr.reset(new int(ptrValueRef));
    EXPECT_EQ(*ptr, ptrValueRef);

    ptr.reset();
    EXPECT_FALSE(ptr.get());
}

TEST_F(ClassUnderTestFixture, ReleaseUniquePtr)
{

    int* wskRel = ptr.release();

    EXPECT_FALSE(ptr.get());
    EXPECT_EQ(*wskRel, *wsk);

    delete wskRel;
}

TEST_F(ClassUnderTestFixture, AssignUniquePtr)
{

    Unique<int> ptrAss = std::move(ptr);

    EXPECT_EQ(*ptrAss, *wsk);
    EXPECT_EQ(*ptrAss, ptrValue);
    EXPECT_FALSE(ptr.get());
    EXPECT_THROW(*ptr, std::runtime_error);
}

TEST_F(ClassUnderTestFixture, MoveAssignOperatorOfUniquePtr)
{

    Unique<int> ptrMoved{};

    ptrMoved = std::move(ptr);

    EXPECT_EQ(*ptrMoved, ptrValue);
    EXPECT_FALSE(ptr.get());
    EXPECT_TRUE(ptrMoved.get());
    EXPECT_THROW(*ptr, std::runtime_error);
}

TEST(UniquePtrTest, ArrowOperatorOfUniquePtr)
{

    std::vector<int>* vec = new std::vector<int>{ 1, 2, 3, 4, 5 };
    Unique<std::vector<int> > vec_ptr{ vec };

    EXPECT_EQ(vec_ptr->front(), (*vec)[0]);
}
