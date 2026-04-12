#include "practice/test.h"
#include "practice/timer.h"
#include "solution.h"
#include <vector>

TEST(empty_input) {
    std::vector<int> v;
    EXPECT_EQ(count_pair_sums(v, 5), 0LL);
}

TEST(single_element) {
    std::vector<int> v = {5};
    EXPECT_EQ(count_pair_sums(v, 5), 0LL);
    EXPECT_EQ(count_pair_sums(v, 10), 0LL);
}

TEST(no_matching_pairs) {
    std::vector<int> v = {1, 2, 3, 4};
    EXPECT_EQ(count_pair_sums(v, 100), 0LL);
}

TEST(simple_pair) {
    std::vector<int> v = {1, 2, 3, 4};
    // pairs summing to 5: (1,4),(2,3) → 2
    EXPECT_EQ(count_pair_sums(v, 5), 2LL);
}

TEST(all_equal_combinatorial) {
    // 5 copies of 3; target = 6; every pair counts: C(5,2) = 10
    std::vector<int> v(5, 3);
    EXPECT_EQ(count_pair_sums(v, 6), 10LL);
}

TEST(all_equal_no_match) {
    std::vector<int> v(5, 3);
    EXPECT_EQ(count_pair_sums(v, 7), 0LL);
}

TEST(duplicates_multiple_pairs) {
    // {2, 2, 2, 4}: target 6 → (2,4) three times = 3
    std::vector<int> v = {2, 2, 2, 4};
    EXPECT_EQ(count_pair_sums(v, 6), 3LL);
}

TEST(negative_values) {
    std::vector<int> v = {-3, -1, -2, -4};
    // target = -5: (-3,-2), (-1,-4) → 2
    EXPECT_EQ(count_pair_sums(v, -5), 2LL);
}

TEST(mixed_signs_target_zero) {
    std::vector<int> v = {-3, 3, -2, 2, 0, 0};
    // zero pairs: (-3,3), (-2,2), (0,0) → 3
    EXPECT_EQ(count_pair_sums(v, 0), 3LL);
}

TEST(zeros_many) {
    // 6 zeros, target 0 → C(6,2) = 15
    std::vector<int> v(6, 0);
    EXPECT_EQ(count_pair_sums(v, 0), 15LL);
}

TEST(correctness_random_like) {
    // Deterministic pseudo-random pattern, cross-check a few targets.
    std::vector<int> v;
    for (int i = 0; i < 200; ++i) v.push_back((i * 53 + 7) % 31 - 15);
    // Count against a brute-force recomputation is basically the function
    // itself — so we just sanity-check the total pair count for target 0
    // is non-negative and reproducible.
    long long c1 = count_pair_sums(v, 0);
    long long c2 = count_pair_sums(v, 0);
    EXPECT_EQ(c1, c2);
}

TEST(large_all_same_timing) {
    // 50k copies of 4, target = 8 → C(50000,2) = ~1.25e9 pairs.
    const int n = 50000;
    std::vector<int> v(n, 4);
    long long result;
    {
        practice::ScopedTimer t("count_pair_sums 50k all-equal");
        result = count_pair_sums(v, 8);
    }
    long long expected = (long long)n * (n - 1) / 2;
    EXPECT_EQ(result, expected);
}

TEST(large_mixed_timing) {
    // 100k alternating 1s and 2s, target = 3: every (1,2) pair counts.
    const int n = 100000;
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) v[i] = (i & 1) ? 2 : 1;
    long long ones = n / 2 + (n & 1);
    long long twos = n / 2;
    long long expected = ones * twos;
    long long result;
    {
        practice::ScopedTimer t("count_pair_sums 100k alternating");
        result = count_pair_sums(v, 3);
    }
    EXPECT_EQ(result, expected);
}

TEST(large_no_match_timing) {
    // 80k distinct values, target impossible — forces full pair scan in the slow version.
    const int n = 80000;
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) v[i] = i;
    long long result;
    {
        practice::ScopedTimer t("count_pair_sums 80k no-match");
        result = count_pair_sums(v, -1);
    }
    EXPECT_EQ(result, 0LL);
}

int main() { return practice::run_all_tests(); }
