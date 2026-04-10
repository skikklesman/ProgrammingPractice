#include "solution.h"

// Search for target in a sorted vector. Return its index, or -1 if absent.
//
// Tests cover:
//   - Target at the beginning, middle, end
//   - Target not present (too small, too large, in a gap)
//   - Single element found / not found
//   - Two elements
//   - Empty vector
//   - Duplicates (should find one of the matching indices)
//   - Large vector (100k elements)
//   - Negative numbers
//
// The code below has subtle bug(s). Find and fix them.
int binary_search(const std::vector<int>& nums, int target) {
    int lo = 0;
    int hi = nums.size();

    while (lo < hi) {
        int mid = (lo + hi) / 2;

        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return -1;
}
