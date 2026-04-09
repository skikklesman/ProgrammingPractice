#include "practice/test.h"
#include "solution.h"
#include <algorithm>

TEST(basic_pair) {
    auto result = two_sum({2, 7, 11, 15}, 9);
    std::sort(result.begin(), result.end());
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
}

TEST(pair_not_at_start) {
    auto result = two_sum({3, 2, 4}, 6);
    std::sort(result.begin(), result.end());
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
}

TEST(negative_numbers) {
    auto result = two_sum({-1, -2, -3, -4, -5}, -8);
    std::sort(result.begin(), result.end());
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 4);
}

int main() { return practice::run_all_tests(); }
