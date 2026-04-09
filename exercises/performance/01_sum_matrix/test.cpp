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

int main() { return practice::run_all_tests(); }
