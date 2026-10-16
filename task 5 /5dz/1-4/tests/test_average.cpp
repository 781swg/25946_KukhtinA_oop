#include "average.h"
#include "average_random.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(AverageTests, NormalNumbers) {
    EXPECT_EQ(orig::average(10, 20), 15);
    EXPECT_EQ(orig::average(4, 6), 5);
}

TEST(AverageTests, NegativeNumbers) {
    EXPECT_EQ(orig::average(-10, 20), 5);
}

TEST(RandomTests, ResultInExpectedRange) {
    int result = modified::average_random(10, 20);
    EXPECT_GE(result, 15);
    EXPECT_LE(result, 25);
}

// Deliberately incorrect tests. Disabled by default to allow normal runs.
TEST(FailureDemo, DISABLED_Expect) {
    EXPECT_EQ(orig::average(10, 20), 100);
    std::cout << "Reached the line after EXPECT\n";
}

TEST(FailureDemo, DISABLED_Assert) {
    ASSERT_EQ(orig::average(10, 20), 100);
    std::cout << "This line after ASSERT will NOT run\n";
}
