#include "make_shared.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace tests {

TEST(MakeSharedShould, createDefaultSharedPtrWhenNoArgumentsPassed) {
    [[maybe_unused]] my::shared_ptr<int> sut = my::make_shared<int>(100);
    [[maybe_unused]] my::shared_ptr<double> sut2 = my::make_shared<double>(200.0);
    [[maybe_unused]] my::shared_ptr<float> sut3 = my::make_shared<float>(300.0f);
    [[maybe_unused]] my::shared_ptr<std::string> sut4 = my::make_shared<std::string>("Some Test");
    [[maybe_unused]] my::shared_ptr<std::pair<int, double>> sut5 =
        my::make_shared<std::pair<int, double>>(10, 20.0);
    [[maybe_unused]] auto sut6 = my::make_shared<int>(100);
}

TEST(MakeSharedShould, createSharedPtrPossibleToBeCopiedToDefaultConstructedSharedPtr) {
    my::shared_ptr<int> sut = my::make_shared<int>(100);
    my::shared_ptr<double> sut2 = my::make_shared<double>(200.0);
    my::shared_ptr<float> sut3 = my::make_shared<float>(300.0f);
    my::shared_ptr<std::string> sut4 = my::make_shared<std::string>("Some Test");
    my::shared_ptr<int> shared;
    my::shared_ptr<double> shared2;
    my::shared_ptr<float> shared3;
    my::shared_ptr<std::string> shared4;

    shared = sut;
    shared2 = sut2;
    shared3 = sut3;
    shared4 = sut4;

    EXPECT_EQ(sut.get(), shared.get());
    EXPECT_EQ(sut2.get(), shared2.get());
    EXPECT_EQ(sut3.get(), shared3.get());
    EXPECT_EQ(sut4.get(), shared4.get());

    EXPECT_EQ(sut.use_count(), shared.use_count());
    EXPECT_EQ(sut2.use_count(), shared2.use_count());
    EXPECT_EQ(sut3.use_count(), shared3.use_count());
    EXPECT_EQ(sut4.use_count(), shared4.use_count());
}

}  // namespace tests
