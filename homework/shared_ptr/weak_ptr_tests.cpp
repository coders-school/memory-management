#include "weak_ptr.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

// TODO: VERIFY if not my namespace
namespace tests {

TEST(WeakPtrShould, bePossibleToBeCratedUsingDefaultConstructor) {
    [[maybe_unused]] my::weak_ptr<int> sut{};
    [[maybe_unused]] my::weak_ptr<double> sut2{};
    [[maybe_unused]] my::weak_ptr<std::string> sut3;
}

// TODO: VERIFY remove or refactor when ptr access after lock() available
//  TEST(WeakPtrShould, storeNullPtrAfterCreationWithDefaultConstructor) {
//      my::weak_ptr<int> sut{};
//      my::weak_ptr<double> sut2{};
//      my::weak_ptr<std::string> sut3;

//     EXPECT_EQ(sut.get(), nullptr);
//     EXPECT_EQ(sut2.get(), nullptr);
//     EXPECT_EQ(sut3.get(), nullptr);
// }

}  // namespace tests