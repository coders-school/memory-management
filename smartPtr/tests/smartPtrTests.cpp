#include <gtest/gtest.h>
#include "smartPtr.hpp"

TEST(smartPtrTests, canConstructSmartPtr)
{
    smartPointer<int> smartPtr(new int(11));
}

