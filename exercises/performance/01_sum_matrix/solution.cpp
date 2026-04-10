#include "solution.h"

// Sum all elements of a 2D matrix stored as a flat vector in row-major order.
// Element (r, c) lives at index [r * cols + c].
//
// Tests cover:
//   - Small 2x3 matrix: {1,2,3,4,5,6} → 21
//   - Single element: {42} → 42
//   - Large 4000x4000 matrix (16M elements): correctness check + timing printout
//
// The code below gives the right answer but iterates column-first, causing a
// cache miss on nearly every access. Reorder the loops for a row-first traversal
// and observe the speedup on the large matrix test.
long long sum_matrix(const std::vector<int>& matrix, int rows, int cols) {
    long long total = 0;

    // This is correct but cache-unfriendly. Make it faster!
    /*for (int c = 0; c < cols; ++c) {
        for (int r = 0; r < rows; ++r) {
            total += matrix[r * cols + c];
        }
    }*/

    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c) {
            total += matrix[r * cols + c];
        }

    return total;
}
