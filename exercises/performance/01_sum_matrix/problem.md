# Performance: Sum a Matrix

`sum_matrix()` computes the sum of all elements in a 2D matrix stored as a
flat `std::vector<int>` in row-major order. The provided implementation is
**correct but slow** due to a cache-unfriendly access pattern.

## Goal

1. Run the tests — they will pass but also print timing information.
2. Optimize `sum_matrix()` so it runs significantly faster on large matrices.
3. Do **not** change the function signature or the tests.

## Hint

Think about how a row-major matrix is laid out in memory and how the CPU cache
works.
