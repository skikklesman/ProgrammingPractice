#include "solution.h"

long long sum_matrix(const std::vector<int>& matrix, int rows, int cols) {
    long long total = 0;

    // This is correct but cache-unfriendly. Make it faster!
    for (int c = 0; c < cols; ++c) {
        for (int r = 0; r < rows; ++r) {
            total += matrix[r * cols + c];
        }
    }

    return total;
}
