#include "solution.h"

// Count unordered pairs (i < j) with v[i] + v[j] == target.
//
// Tests cover:
//   - Empty and single-element inputs (zero pairs)
//   - No matching pairs
//   - All elements equal (combinatorial count)
//   - Negative values and mixed signs
//   - Duplicates contributing multiple pairs
//   - Large inputs with many hits (timing)
//
// The implementation below tries every pair — O(n^2). Replace it with an
// O(n) pass using an unordered_map keyed by value (count of occurrences
// seen so far); for each element v[i], add the count of (target - v[i]).
long long count_pair_sums(const std::vector<int>& v, int target) {
    long long count = 0;
    int n = (int)v.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (v[i] + v[j] == target) {
                ++count;
            }
        }
    }
    return count;
}
