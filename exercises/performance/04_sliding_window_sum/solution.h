#pragma once
#include <vector>

// Return a vector where result[i] = sum of v[i..i+k-1].
// Output size is v.size() - k + 1, or empty if k > v.size() or k <= 0.
std::vector<long long> window_sums(const std::vector<int>& v, int k);
