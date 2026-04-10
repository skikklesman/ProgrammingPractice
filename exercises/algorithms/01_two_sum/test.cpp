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

TEST(two_elements) {
    auto result = two_sum({1, 2}, 3);
    std::sort(result.begin(), result.end());
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
}

TEST(pair_at_end) {
    // 9 + 2 = 11 → indices 4 and 5
    auto result = two_sum({1, 3, 5, 7, 9, 2}, 11);
    std::sort(result.begin(), result.end());
    EXPECT_EQ(result[0], 4);
    EXPECT_EQ(result[1], 5);
}

TEST(zeros) {
    auto result = two_sum({0, 4, 0, 3}, 0);
    std::sort(result.begin(), result.end());
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 2);
}

TEST(target_zero_with_negatives) {
    auto result = two_sum({5, -5, 10, -10}, 0);
    std::sort(result.begin(), result.end());
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
}

TEST(large_values) {
    auto result = two_sum({1000000, 500000, -1000000, 250000}, 0);
    std::sort(result.begin(), result.end());
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 2);
}

TEST(negative_target_positive_numbers) {
    // No pair of positive numbers sums to a negative... so use mixed
    auto result = two_sum({-10, 3, 7, -3, 1}, -9);
    std::sort(result.begin(), result.end());
    // -10 + 1 = -9 → indices 0 and 4
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 4);
}

TEST(duplicates_in_array) {
    auto result = two_sum({3, 3, 3, 3}, 6);
    std::sort(result.begin(), result.end());
    EXPECT_EQ(result.size(), 2u);
    // First pair found: indices 0 and 1
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
}

TEST(large_array) {
    // Build a big array where the answer is at the very end
    std::vector<int> nums(10000, 0);
    nums[9998] = 42;
    nums[9999] = 58;
    auto result = two_sum(nums, 100);
    std::sort(result.begin(), result.end());
    EXPECT_EQ(result[0], 9998);
    EXPECT_EQ(result[1], 9999);
}

TEST(answer_at_first_and_last) {
    auto result = two_sum({50, 1, 2, 3, 4, 5, 6, 7, 8, 9, 50}, 100);
    std::sort(result.begin(), result.end());
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 10);
}

TEST(single_negative_pair) {
    auto result = two_sum({1, -1}, 0);
    std::sort(result.begin(), result.end());
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
}

int main() { return practice::run_all_tests(); }
