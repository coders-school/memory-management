#include "shared_ptr.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace tests {

TEST(MakeSharedShould, createSharedPtrFromGivenArguments) {
    [[maybe_unused]] my::shared_ptr<int> = my::make_shared(100);
}

}  // namespace tests