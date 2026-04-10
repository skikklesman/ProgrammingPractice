#include "solution.h"

// Build a comma-separated string of integers from 0 to n-1.
// Example: build_sequence(4) → "0,1,2,3"
//
// Tests cover:
//   - n=0 → ""
//   - n=1 → "0"
//   - n=5 → "0,1,2,3,4"
//   - n=100000 → correctness + timing (this is where the slowness shows)
//   - n=200000 → bigger stress test with timing
//
// The code below creates a new temporary string on every iteration via the
// `+` operator. Each `+` allocates, copies, and frees. Over many iterations
// this is O(n²) in total work. Find a way to build the string in O(n).
std::string build_sequence(int n) {
    std::string result = "";

    // Slow: each `+` creates a temporary copy of the growing string
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            result = result + ",";
        }
        result = result + std::to_string(i);
    }

    return result;
}
