#include "uniquePtrut.h"

#include "gtest/gtest.h"


class UniquePtrShould : public testing::Test
{
public:
    UniquePtrShould() : sut(new int(10)) {}
protected:
    UniquePtr<int> sut_;
};

TEST_F(UniquePtrShould, Dereference)
{
    EXPECTEQ(*sut, 10);
}

TEST_F(UniquePtrShould, CompareValues)
{
    UniquePtr<int> ptr (new int (20));
    EXPECTNE(*sut, ptr);
}

TESTF(UniquePtrShould, Reset)
{
    sut.reset();
    auto resetedPtr = sut_.get();
    EXPECT_EQ(resetedPtr, nullptr);
}

TESTF(UniquePtrShould, Release)
{
    auto newPtr = sut.release();
    EXPECTEQ(sut.get(), nullptr);
    EXPECT_EQ(newPtr, 10);
}

TEST_F(UniquePtrShould, Get)
{
    EXPECTEQ(typeid(*sut.get()).name(), typeid(int).name());
}

TESTF(UniquePtrShould, Move)
{
    UniquePtr<int> temp = std::move(sut);
    EXPECT_EQ(*temp, 10);
    EXPECTEQ(sut.get(), nullptr);
}