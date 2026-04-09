#pragma once
#include <string>
#include <vector>

// Split `s` by `delim` and return the tokens.
// An empty input returns a single empty string {""}.
// Consecutive delimiters produce empty tokens.
std::vector<std::string> split(const std::string& s, char delim);
