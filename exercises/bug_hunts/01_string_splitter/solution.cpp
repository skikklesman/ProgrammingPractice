#include "solution.h"

// Split a string by a single-character delimiter and return the tokens.
// Consecutive delimiters produce empty tokens, e.g. "a,,b" → {"a","","b"}.
//
// Tests cover:
//   - Simple split: "a,b,c" by ',' → {"a","b","c"}
//   - Empty input: "" → {""} (one empty token, not zero)
//   - No delimiter found: "hello" by ',' → {"hello"}
//   - Consecutive delimiters: "a,,b" → {"a","","b"}
//   - Trailing delimiter: "a,b," → {"a","b",""}
//
// The code below compiles and runs but produces wrong results in several of
// the above cases. Read the tests, run them, and fix the bugs.
std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> tokens;
    std::string current = "";

    // BUG(s) lurk below — find and fix them.
    int size = s.size();

    for (size_t i = 0; i < size; i++) {
        if (s[i] == delim) {
            tokens.push_back(current);
            // Clear out current now that we've pushed it into tokens
            current.clear();
        } else {
            current += s[i];
        }
    }

    // When we finish, we still have a last current string to push
    tokens.push_back(current);

    return tokens;
}
