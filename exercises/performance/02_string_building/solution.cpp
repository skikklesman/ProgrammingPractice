#include "solution.h"
#include <charconv>

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
    
    // Original implementation (Slow): each `+` creates a temporary copy of the growing string
    // std::string result = "";
    /*for (int i = 0; i < n; ++i) {
        if (i > 0) {
            result = result + ",";
        }
        result = result + std::to_string(i);
    }*/


    // New optimized solution:
    // Pre-allocate all of the space needed, then just fill in each slot as you go
    // Space needed:
    //  * n-1 ',' characters
    //  * (num digits in biggest number) times n
    std::string result = "";

    if (0 == n)
        return result;

    int digitsInBiggestNumber = int(log10(n)) + 1;
    size_t necessaryStringCapacity = (n * digitsInBiggestNumber) + (n-1);
    result.reserve(necessaryStringCapacity);

    for (int i = 0; i < n; ++i)
    {
        if (i > 0) {
            result.push_back(',');
        }

        char buf[20]{};
        std::to_chars_result toCharsResult = std::to_chars(buf, buf + 20, i);
        std::string_view str(buf, toCharsResult.ptr-buf);
        result.append(str);
    }

    return result;
}
