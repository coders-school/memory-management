#include <gtest/gtest.h>
#include "smartPtr.hpp"

class smartPointerTests : public ::testing::Test
{
public:
    smartPointerTests()
    {
    }
    ~smartPointerTests()
    {
    }
private:
};

TEST(smartPtrTests, canConstructSmartPtr)
{
    smartPointer<int> smartPtr(new int(11));
}

TEST_F(smartPointerTests, resetPtr1)
{
    smartPointer<int> smPtr1(new int(1));
    smPtr1.reset();
}

TEST_F(smartPointerTests, resetPtr2)
{
    smartPointer<int> smPtr1(new int(1));
    smPtr1.reset(new int(2));
}

