#include "solution.h"

// Answer many range-sum queries over a fixed vector.
//
// Tests cover:
//   - Empty query list (but non-empty vector)
//   - Single-element ranges (l == r)
//   - Full-vector range
//   - Negative values, mixed signs
//   - Large values requiring long long accumulation
//   - Many queries over a large vector (timing)
//
// The implementation below loops through each query and sums v[l..r] from
// scratch — O(q * n) in the worst case. Precompute a prefix-sum table once
// so each query can be answered in O(1) as prefix[r+1] - prefix[l].
std::vector<long long> range_sums(
    const std::vector<int>& v,
    const std::vector<std::pair<int, int>>& queries) {
    std::vector<long long> answers;
    answers.reserve(queries.size());
    for (const auto& q : queries) {
        long long s = 0;
        for (int i = q.first; i <= q.second; ++i) {
            s += v[i];
        }
        answers.push_back(s);
    }
    return answers;
}
