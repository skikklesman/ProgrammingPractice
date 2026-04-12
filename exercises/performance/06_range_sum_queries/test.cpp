#include "practice/test.h"
#include "practice/timer.h"
#include "solution.h"
#include <vector>
#include <utility>

TEST(no_queries) {
    std::vector<int> v = {1, 2, 3, 4};
    std::vector<std::pair<int, int>> q;
    auto r = range_sums(v, q);
    EXPECT_EQ(r.size(), (size_t)0);
}

TEST(single_point_queries) {
    std::vector<int> v = {10, 20, 30, 40};
    std::vector<std::pair<int, int>> q = {{0, 0}, {2, 2}, {3, 3}};
    std::vector<long long> expected = {10, 30, 40};
    EXPECT_EQ(range_sums(v, q), expected);
}

TEST(full_range) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<std::pair<int, int>> q = {{0, 4}};
    std::vector<long long> expected = {15};
    EXPECT_EQ(range_sums(v, q), expected);
}

TEST(hand_checked) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<std::pair<int, int>> q = {{0, 2}, {1, 4}, {3, 5}, {2, 2}};
    // sums: 1+2+3=6, 2+3+4+5=14, 4+5+6=15, 3
    std::vector<long long> expected = {6, 14, 15, 3};
    EXPECT_EQ(range_sums(v, q), expected);
}

TEST(negative_values) {
    std::vector<int> v = {-1, -2, -3, -4};
    std::vector<std::pair<int, int>> q = {{0, 3}, {1, 2}};
    std::vector<long long> expected = {-10, -5};
    EXPECT_EQ(range_sums(v, q), expected);
}

TEST(mixed_signs_cancel) {
    std::vector<int> v = {5, -5, 5, -5, 5, -5};
    std::vector<std::pair<int, int>> q = {{0, 5}, {0, 0}, {0, 1}, {2, 4}};
    // 0, 5, 0, 5
    std::vector<long long> expected = {0, 5, 0, 5};
    EXPECT_EQ(range_sums(v, q), expected);
}

TEST(large_values_need_long_long) {
    std::vector<int> v(10, 2000000000);
    std::vector<std::pair<int, int>> q = {{0, 9}};
    std::vector<long long> expected = {20000000000LL};
    EXPECT_EQ(range_sums(v, q), expected);
}

TEST(overlapping_queries_consistency) {
    std::vector<int> v = {4, 1, 7, 2, 8, 3};
    std::vector<std::pair<int, int>> q = {{0, 5}, {0, 2}, {3, 5}};
    // sum full = 25, 0..2 = 12, 3..5 = 13
    auto r = range_sums(v, q);
    EXPECT_EQ(r[0], 25LL);
    EXPECT_EQ(r[1], 12LL);
    EXPECT_EQ(r[2], 13LL);
    EXPECT_EQ(r[1] + r[2], r[0]);
}

TEST(many_small_queries_timing) {
    // 100k elements, 100k full-range queries — naive = 1e10 ops.
    const int n = 100000;
    const int q = 100000;
    std::vector<int> v(n, 1);
    std::vector<std::pair<int, int>> queries;
    queries.reserve(q);
    for (int i = 0; i < q; ++i) queries.push_back({0, n - 1});

    std::vector<long long> result;
    {
        practice::ScopedTimer t("range_sums 100k v, 100k full-range q");
        result = range_sums(v, queries);
    }
    EXPECT_EQ(result.size(), (size_t)q);
    EXPECT_EQ(result.front(), (long long)n);
    EXPECT_EQ(result.back(), (long long)n);
}

TEST(varied_query_timing) {
    // 200k elements, 200k varied queries with deterministic ranges.
    const int n = 200000;
    const int q = 200000;
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) v[i] = (i % 7) - 3;

    std::vector<std::pair<int, int>> queries;
    queries.reserve(q);
    for (int i = 0; i < q; ++i) {
        int l = (i * 31) % n;
        int len = (i * 17) % n;
        int r = l + len;
        if (r >= n) r = n - 1;
        queries.push_back({l, r});
    }

    std::vector<long long> result;
    {
        practice::ScopedTimer t("range_sums 200k v, 200k varied q");
        result = range_sums(v, queries);
    }
    EXPECT_EQ(result.size(), (size_t)q);
}

TEST(small_ranges_large_count_timing) {
    // 1M elements, 500k short queries (length ~10). Naive is fine-ish but
    // prefix sums still win.
    const int n = 1000000;
    const int q = 500000;
    std::vector<int> v(n, 1);
    std::vector<std::pair<int, int>> queries;
    queries.reserve(q);
    for (int i = 0; i < q; ++i) {
        int l = (i * 13) % (n - 10);
        queries.push_back({l, l + 9});
    }
    std::vector<long long> result;
    {
        practice::ScopedTimer t("range_sums 1M v, 500k len-10 q");
        result = range_sums(v, queries);
    }
    EXPECT_EQ(result.size(), (size_t)q);
    EXPECT_EQ(result.front(), 10LL);
}

int main() { return practice::run_all_tests(); }
