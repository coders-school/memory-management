#include "unique_ptr.hpp"
#include <gtest/gtest.h>

constexpr int kValue{3};
template class my::unique_ptr<int>;

class UniquePtrIntFixture : public ::testing::Test
{
public:
    UniquePtrIntFixture() : ptr{new int(kValue)}, ut(ptr) {}

protected:
    int* ptr;
    my::unique_ptr<int> ut;
};

TEST_F(UniquePtrIntFixture, GivenWellInstance_WhenExtractValue_ThenGetValue)
{
    // When
    auto actual_value = *ut;

    // Then
    auto expected_value{kValue};
    EXPECT_EQ(actual_value, expected_value);
}


TEST_F(UniquePtrIntFixture, GivenWellInstance_WhenTryToBeCopied_ThenGetError)
{
    // Then
    my::unique_ptr<int> second(std::move(ut));

    // When
    EXPECT_EQ(*second, kValue);
}

TEST_F(UniquePtrIntFixture, GivenWellInstance_WhenGetToNewPointerVariable_ThenExpectThePointerIsTheSameAsWasGiven)
{
    // Then
    auto second_ptr(ut.get());

    // When
    EXPECT_EQ(ptr, second_ptr);
}

TEST_F(UniquePtrIntFixture, GivenWellInstance_WhenReleaseToNewPointerVariable_ThenExpectThePointerIsTheSameAsWasGivenAndTheUThasNullPtr)
{
    // Then
    auto second_ptr(ut.release());
    auto third_ptr(ut.get());

    // When
    EXPECT_EQ(ptr, second_ptr);
    EXPECT_EQ(third_ptr, nullptr);
}


TEST_F(UniquePtrIntFixture, GivenWellInstance_WhenResetToNewPointer_ThenExpectThePointerWithNewValue)
{
    // Then
    auto second_ptr{new int(kValue)};
    ut.reset(second_ptr);

    // When
    EXPECT_EQ(ut.get(), second_ptr);
}

TEST_F(UniquePtrIntFixture, GivenWellInstance_WhenReset_ThenExpectNullpointerFromGet)
{
    // Then
    ut.reset();

    // When
    EXPECT_EQ(ut.get(), nullptr);
}

TEST_F(UniquePtrIntFixture, GivenWellInstance_WhenResetTwice_ThenExpectNullpointerFromGet)
{
    // Then
    ut.reset();
    ut.reset();

    // When
    EXPECT_EQ(ut.get(), nullptr);
}

TEST_F(UniquePtrIntFixture, GivenWellInstance_WhenResetSecondTimeWithWellValue_ThenExpectThePointerWithNewValue)
{
    // Then
    ut.reset();
    auto second_ptr{new int(kValue)};
    ut.reset(second_ptr);

    //When
    EXPECT_EQ(ut.get(), second_ptr);
}

TEST_F(UniquePtrIntFixture, GivenWellInstance_WhenMoveAssignNewResourceToOld_ThenExpectOldResourceToBeFreed)
{
    // Then
    ut = my::unique_ptr<int>(new int(kValue + 1));

    //When
    EXPECT_EQ(*ut.get(), kValue + 1);
}

