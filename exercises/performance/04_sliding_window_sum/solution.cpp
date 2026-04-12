#include "solution.h"

// Compute the sum of every contiguous window of size k in v.
// Example: window_sums({1,2,3,4,5}, 3) → {6, 9, 12}
//
// Tests cover:
//   - Empty input, k larger than size, k == size
//   - k == 1 (sums equal the input, cast to long long)
//   - Small hand-checked examples
//   - Negative values and mixed signs
//   - Large values that require long long accumulation
//   - Large inputs with small and large k (timing)
//
// The implementation below re-sums each window from scratch — O(n*k).
// Optimize it to O(n) using a running sum: when the window slides, subtract
// the element leaving and add the element entering.
std::vector<long long> window_sums(const std::vector<int>& v, int k) {
    std::vector<long long> result;
    int n = (int)v.size();
    if (k <= 0 || k > n) return result;

    result.reserve(n - k + 1);
    for (int i = 0; i + k <= n; ++i) {
        long long sum = 0;
        for (int j = 0; j < k; ++j) {
            sum += v[i + j];
        }
        result.push_back(sum);
    }
    return result;
}
