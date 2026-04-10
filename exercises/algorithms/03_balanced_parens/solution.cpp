#include "solution.h"

// Determine whether a string of brackets — (){}[] — is properly balanced.
// Every opener must have a matching closer in the correct nesting order.
//
// Tests cover:
//   - Simple pairs: "()", "[]", "{}"
//   - Multiple types in sequence: "()[]{}"
//   - Nested brackets: "{[]}", "({[]})"
//   - Mismatched types: "(]", "{)"
//   - Wrong nesting order: "([)]"
//   - Extra openers: "((("
//   - Extra closers: ")))"
//   - Single bracket: "(" or ")"
//   - Empty string: "" → true
//   - Long deeply nested input
//
// Hint: a stack is the natural fit here.
bool is_balanced(const std::string& s) {
    // TODO: implement
    return false;
}
