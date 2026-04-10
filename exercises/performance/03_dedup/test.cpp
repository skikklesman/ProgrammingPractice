#include "practice/test.h"
#include "practice/timer.h"
#include "solution.h"

TEST(empty_input) {
    auto result = dedup({});
    EXPECT(result.empty());
}

TEST(no_duplicates) {
    auto result = dedup({1, 2, 3, 4, 5});
    std::vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(result, expected);
}

TEST(all_identical) {
    auto result = dedup({7, 7, 7, 7, 7});
    std::vector<int> expected = {7};
    EXPECT_EQ(result, expected);
}

TEST(general_case) {
    auto result = dedup({3, 1, 4, 1, 5, 9, 2, 6, 5, 3});
    std::vector<int> expected = {3, 1, 4, 5, 9, 2, 6};
    EXPECT_EQ(result, expected);
}

TEST(preserves_first_occurrence_order) {
    auto result = dedup({5, 3, 5, 1, 3, 1});
    std::vector<int> expected = {5, 3, 1};
    EXPECT_EQ(result, expected);
}

TEST(single_element) {
    auto result = dedup({42});
    std::vector<int> expected = {42};
    EXPECT_EQ(result, expected);
}

TEST(two_same) {
    auto result = dedup({1, 1});
    std::vector<int> expected = {1};
    EXPECT_EQ(result, expected);
}

TEST(two_different) {
    auto result = dedup({1, 2});
    std::vector<int> expected = {1, 2};
    EXPECT_EQ(result, expected);
}

TEST(negative_numbers) {
    auto result = dedup({-3, -1, -3, -2, -1});
    std::vector<int> expected = {-3, -1, -2};
    EXPECT_EQ(result, expected);
}

TEST(mixed_signs) {
    auto result = dedup({1, -1, 0, 1, -1, 0});
    std::vector<int> expected = {1, -1, 0};
    EXPECT_EQ(result, expected);
}

TEST(large_many_duplicates_timing) {
    // 100k elements but only values 0-99 — tons of duplicates
    const int n = 100000;
    std::vector<int> input(n);
    for (int i = 0; i < n; ++i) input[i] = i % 100;

    std::vector<int> result;
    {
        practice::ScopedTimer t("dedup 100k elements, 100 unique");
        result = dedup(input);
    }
    EXPECT_EQ(result.size(), 100u);
    // First 100 elements should be 0,1,2,...,99
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(result[i], i);
    }
}

TEST(large_all_unique_timing) {
    // 100k elements, all unique — worst case for the naive approach
    const int n = 100000;
    std::vector<int> input(n);
    for (int i = 0; i < n; ++i) input[i] = i;

    std::vector<int> result;
    {
        practice::ScopedTimer t("dedup 100k elements, all unique");
        result = dedup(input);
    }
    EXPECT_EQ(result.size(), (size_t)n);
}

int main() { return practice::run_all_tests(); }
