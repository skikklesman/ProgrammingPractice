#include "solution.h"

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> tokens;
    std::string current;

    // BUG(s) lurk below — find and fix them.
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == delim) {
            tokens.push_back(current);
        } else {
            current += s[i];
        }
    }

    return tokens;
}
