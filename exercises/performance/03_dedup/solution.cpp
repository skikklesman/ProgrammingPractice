#include "solution.h"

// Remove duplicates from a vector, preserving the order of first occurrences.
// Example: {3,1,4,1,5,9,2,6,5,3} → {3,1,4,5,9,2,6}
//
// Tests cover:
//   - Empty input → {}
//   - No duplicates → unchanged
//   - All identical → single element
//   - General case with scattered duplicates
//   - Negative numbers and mixed signs
//   - Large input (100k elements, many duplicates) with timing
//   - Large input (100k unique elements) with timing
//
// The code below checks every earlier element for each new element — O(n²).
// Optimize it using a data structure that supports fast lookups.
std::vector<int> dedup(const std::vector<int>& input) {
    std::vector<int> result;

    // Slow: for each element, scan all of result to check for duplicates
    for (size_t i = 0; i < input.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < result.size(); ++j) {
            if (result[j] == input[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            result.push_back(input[i]);
        }
    }

    return result;
}
