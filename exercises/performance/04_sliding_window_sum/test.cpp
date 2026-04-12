#include "practice/test.h"
#include "practice/timer.h"
#include "solution.h"
#include <vector>
#include <numeric>
#include <random>

TEST(empty_input) {
    std::vector<int> v;
    auto r = window_sums(v, 3);
    EXPECT_EQ(r.size(), (size_t)0);
}

TEST(k_larger_than_size) {
    std::vector<int> v = {1, 2, 3};
    auto r = window_sums(v, 5);
    EXPECT_EQ(r.size(), (size_t)0);
}

TEST(k_zero_or_negative) {
    std::vector<int> v = {1, 2, 3};
    EXPECT_EQ(window_sums(v, 0).size(), (size_t)0);
    EXPECT_EQ(window_sums(v, -2).size(), (size_t)0);
}

TEST(k_equals_size) {
    std::vector<int> v = {1, 2, 3, 4};
    std::vector<long long> expected = {10};
    EXPECT_EQ(window_sums(v, 4), expected);
}

TEST(k_one_equals_input) {
    std::vector<int> v = {5, -3, 7, 0, 2};
    std::vector<long long> expected = {5, -3, 7, 0, 2};
    EXPECT_EQ(window_sums(v, 1), expected);
}

TEST(simple_example) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<long long> expected = {6, 9, 12};
    EXPECT_EQ(window_sums(v, 3), expected);
}

TEST(all_zeros) {
    std::vector<int> v(10, 0);
    auto r = window_sums(v, 4);
    EXPECT_EQ(r.size(), (size_t)7);
    for (auto x : r) EXPECT_EQ(x, 0LL);
}

TEST(negative_values) {
    std::vector<int> v = {-1, -2, -3, -4};
    std::vector<long long> expected = {-3, -5, -7};
    EXPECT_EQ(window_sums(v, 2), expected);
}

TEST(mixed_signs) {
    std::vector<int> v = {4, -1, 2, -3, 5, -2};
    // windows of size 3: {4,-1,2}=5, {-1,2,-3}=-2, {2,-3,5}=4, {-3,5,-2}=0
    std::vector<long long> expected = {5, -2, 4, 0};
    EXPECT_EQ(window_sums(v, 3), expected);
}

TEST(large_values_overflow_check) {
    // Each window sums four near-INT_MAX values — needs long long.
    std::vector<int> v(8, 2000000000);
    auto r = window_sums(v, 4);
    EXPECT_EQ(r.size(), (size_t)5);
    for (auto x : r) EXPECT_EQ(x, 8000000000LL);
}

TEST(correctness_medium) {
    // Cross-check against a slow reference for a random-ish input.
    std::vector<int> v;
    for (int i = 0; i < 1000; ++i) v.push_back((i * 37 + 11) % 97 - 50);
    int k = 25;
    auto got = window_sums(v, k);
    EXPECT_EQ(got.size(), (size_t)(v.size() - k + 1));
    for (size_t i = 0; i < got.size(); ++i) {
        long long s = 0;
        for (int j = 0; j < k; ++j) s += v[i + j];
        EXPECT_EQ(got[i], s);
    }
}

TEST(large_window_timing) {
    // n = 200k, k = 5000 — naive is ~1e9 ops.
    const int n = 200000, k = 5000;
    std::vector<int> v(n, 1);
    std::vector<long long> result;
    {
        practice::ScopedTimer t("window_sums 200k, k=5000");
        result = window_sums(v, k);
    }
    EXPECT_EQ(result.size(), (size_t)(n - k + 1));
    EXPECT_EQ(result.front(), (long long)k);
    EXPECT_EQ(result.back(), (long long)k);
}

TEST(huge_window_timing) {
    // n = 500k, k = 10000 — naive is ~5e9 ops.
    const int n = 500000, k = 10000;
    std::vector<int> v(n, 2);
    std::vector<long long> result;
    {
        practice::ScopedTimer t("window_sums 500k, k=10000");
        result = window_sums(v, k);
    }
    EXPECT_EQ(result.size(), (size_t)(n - k + 1));
    EXPECT_EQ(result.front(), (long long)k * 2);
}

TEST(small_window_large_n_timing) {
    // n = 5M, k = 3 — mostly stresses the output loop, should be fast both ways.
    const int n = 5000000, k = 3;
    std::vector<int> v(n, 1);
    std::vector<long long> result;
    {
        practice::ScopedTimer t("window_sums 5M, k=3");
        result = window_sums(v, k);
    }
    EXPECT_EQ(result.size(), (size_t)(n - k + 1));
    EXPECT_EQ(result.front(), 3LL);
}

int main() { return practice::run_all_tests(); }
