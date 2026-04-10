#include "practice/test.h"
#include "solution.h"
#include <numeric>

TEST(basic_merge) {
    auto result = merge_sorted({1, 3, 5}, {2, 4, 6});
    std::vector<int> expected = {1, 2, 3, 4, 5, 6};
    EXPECT_EQ(result, expected);
}

TEST(first_empty) {
    auto result = merge_sorted({}, {1, 2, 3});
    std::vector<int> expected = {1, 2, 3};
    EXPECT_EQ(result, expected);
}

TEST(second_empty) {
    auto result = merge_sorted({4, 5, 6}, {});
    std::vector<int> expected = {4, 5, 6};
    EXPECT_EQ(result, expected);
}

TEST(both_empty) {
    auto result = merge_sorted({}, {});
    EXPECT(result.empty());
}

TEST(duplicates_across) {
    auto result = merge_sorted({1, 2, 3}, {2, 3, 4});
    std::vector<int> expected = {1, 2, 2, 3, 3, 4};
    EXPECT_EQ(result, expected);
}

TEST(all_same) {
    auto result = merge_sorted({1, 1, 1}, {1, 1});
    std::vector<int> expected = {1, 1, 1, 1, 1};
    EXPECT_EQ(result, expected);
}

TEST(different_lengths) {
    auto result = merge_sorted({1}, {2, 3, 4, 5, 6, 7, 8});
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8};
    EXPECT_EQ(result, expected);
}

TEST(negative_numbers) {
    auto result = merge_sorted({-5, -3, -1}, {-4, -2, 0});
    std::vector<int> expected = {-5, -4, -3, -2, -1, 0};
    EXPECT_EQ(result, expected);
}

TEST(mixed_signs) {
    auto result = merge_sorted({-10, 0, 10}, {-5, 5, 15});
    std::vector<int> expected = {-10, -5, 0, 5, 10, 15};
    EXPECT_EQ(result, expected);
}

TEST(non_overlapping_ranges) {
    auto result = merge_sorted({1, 2, 3}, {10, 20, 30});
    std::vector<int> expected = {1, 2, 3, 10, 20, 30};
    EXPECT_EQ(result, expected);
}

TEST(single_elements) {
    auto result = merge_sorted({5}, {3});
    std::vector<int> expected = {3, 5};
    EXPECT_EQ(result, expected);
}

TEST(large_inputs) {
    const int n = 100000;
    std::vector<int> a(n), b(n);
    // a = {0, 2, 4, 6, ...}  b = {1, 3, 5, 7, ...}
    for (int i = 0; i < n; ++i) {
        a[i] = i * 2;
        b[i] = i * 2 + 1;
    }
    auto result = merge_sorted(a, b);
    EXPECT_EQ(result.size(), (size_t)(2 * n));
    // Result should be {0, 1, 2, 3, ...}
    for (int i = 0; i < 2 * n; ++i) {
        EXPECT_EQ(result[i], i);
    }
}

int main() { return practice::run_all_tests(); }
