#pragma once
#include <vector>

// Count unordered index pairs (i, j) with i < j and v[i] + v[j] == target.
long long count_pair_sums(const std::vector<int>& v, int target);
