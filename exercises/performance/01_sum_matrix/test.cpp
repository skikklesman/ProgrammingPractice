#include "practice/test.h"
#include "practice/timer.h"
#include "solution.h"
#include <numeric>

TEST(small_matrix) {
    //  1  2  3
    //  4  5  6
    std::vector<int> m = {1, 2, 3, 4, 5, 6};
    EXPECT_EQ(sum_matrix(m, 2, 3), 21LL);
}

TEST(single_element) {
    std::vector<int> m = {42};
    EXPECT_EQ(sum_matrix(m, 1, 1), 42LL);
}

TEST(single_row) {
    std::vector<int> m = {10, 20, 30, 40, 50};
    EXPECT_EQ(sum_matrix(m, 1, 5), 150LL);
}

TEST(single_column) {
    std::vector<int> m = {10, 20, 30, 40, 50};
    EXPECT_EQ(sum_matrix(m, 5, 1), 150LL);
}

TEST(all_zeros) {
    std::vector<int> m(100, 0);
    EXPECT_EQ(sum_matrix(m, 10, 10), 0LL);
}

TEST(all_ones) {
    std::vector<int> m(600, 1);
    EXPECT_EQ(sum_matrix(m, 20, 30), 600LL);
}

TEST(negative_values) {
    std::vector<int> m = {-1, -2, -3, -4, -5, -6};
    EXPECT_EQ(sum_matrix(m, 2, 3), -21LL);
}

TEST(mixed_positive_negative) {
    // Sum should cancel to zero
    std::vector<int> m = {1, -1, 2, -2, 3, -3};
    EXPECT_EQ(sum_matrix(m, 2, 3), 0LL);
}

TEST(large_values) {
    // 4 elements near INT_MAX — tests that long long accumulation works
    std::vector<int> m = {2000000000, 2000000000, 2000000000, 2000000000};
    EXPECT_EQ(sum_matrix(m, 2, 2), 8000000000LL);
}

TEST(wide_matrix_timing) {
    // 1 row, 16M columns — pure sequential access
    const int rows = 1, cols = 16000000;
    std::vector<int> m(cols, 1);
    long long result;
    {
        practice::ScopedTimer t("sum_matrix 1x16M");
        result = sum_matrix(m, rows, cols);
    }
    EXPECT_EQ(result, (long long)cols);
}

TEST(tall_matrix_timing) {
    // 16M rows, 1 column — also sequential, but tests row iteration overhead
    const int rows = 16000000, cols = 1;
    std::vector<int> m(rows, 1);
    long long result;
    {
        practice::ScopedTimer t("sum_matrix 16Mx1");
        result = sum_matrix(m, rows, cols);
    }
    EXPECT_EQ(result, (long long)rows);
}

TEST(large_matrix_correctness_and_timing) {
    const int rows = 4000, cols = 4000;
    std::vector<int> m(rows * cols);
    std::iota(m.begin(), m.end(), 1);  // 1, 2, 3, ...

    long long expected = (long long)(rows * cols) * (rows * cols + 1) / 2;

    long long result;
    {
        practice::ScopedTimer t("sum_matrix 4000x4000");
        result = sum_matrix(m, rows, cols);
    }
    EXPECT_EQ(result, expected);
}

TEST(very_large_square_timing) {
    // 8000x8000 = 64M elements — bigger stress test
    const int rows = 8000, cols = 8000;
    std::vector<int> m(rows * cols, 7);
    long long expected = (long long)rows * cols * 7;
    long long result;
    {
        practice::ScopedTimer t("sum_matrix 8000x8000");
        result = sum_matrix(m, rows, cols);
    }
    EXPECT_EQ(result, expected);
}

TEST(nonsquare_large_timing) {
    // 2000x8000 — wide rectangle
    const int rows = 2000, cols = 8000;
    std::vector<int> m(rows * cols, 3);
    long long expected = (long long)rows * cols * 3;
    long long result;
    {
        practice::ScopedTimer t("sum_matrix 2000x8000");
        result = sum_matrix(m, rows, cols);
    }
    EXPECT_EQ(result, expected);
}

int main() { return practice::run_all_tests(); }
