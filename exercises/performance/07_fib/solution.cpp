#include "solution.h"

// Return the n-th Fibonacci number. fib(0) = 0, fib(1) = 1.
//
// Tests cover:
//   - Base cases: fib(0) = 0, fib(1) = 1
//   - Small values: fib(2) through fib(10)
//   - Specific known values (fib(20), fib(30))
//   - Timing tests at n = 35, 38, 40, 42 — the slow version takes seconds
//     while an iterative version takes microseconds.
//
// The implementation below recomputes the same subproblems exponentially
// many times (T(n) ~= fib(n+1) calls). Rewrite it iteratively: walk from
// 2 up to n, carrying the last two values. O(n) time, O(1) space.
long long fib(int n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}
