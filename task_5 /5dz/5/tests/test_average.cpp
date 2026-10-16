#include "average.h"
#include "average_random.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(AverageTests, Integers) {
    EXPECT_EQ(orig::average(10, 20), 15);
    EXPECT_EQ(orig::average(4, 7), 5); // int division truncates the fraction
}

TEST(AverageTests, Doubles) {
    EXPECT_DOUBLE_EQ(orig::average(10.0, 21.0), 15.5);
}

TEST(RandomTests, IntegersInRange) {
    int result = modified::average_random(10, 20);
    EXPECT_GE(result, 15);
    EXPECT_LE(result, 25);
}

TEST(RandomTests, DoublesInRange) {
    double result = modified::average_random(10.0, 21.0);
    EXPECT_GE(result, 15.5);
    EXPECT_LE(result, 25.5);
}

TEST(FailureDemo, DISABLED_Expect) {
    EXPECT_EQ(orig::average(10, 20), 100);
    std::cout << "Reached the line after EXPECT\n";
}

TEST(FailureDemo, DISABLED_Assert) {
    ASSERT_EQ(orig::average(10, 20), 100);
    std::cout << "This line after ASSERT will NOT run\n";
}
