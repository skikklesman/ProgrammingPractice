#pragma once
#include <vector>
#include <utility>

// For each query (l, r), return the sum of v[l..r] inclusive.
// Assumes 0 <= l <= r < v.size() for every query.
std::vector<long long> range_sums(
    const std::vector<int>& v,
    const std::vector<std::pair<int, int>>& queries);
