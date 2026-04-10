#include "practice/test.h"
#include "solution.h"

TEST(empty_string) {
    EXPECT(is_balanced(""));
}

TEST(simple_parens) {
    EXPECT(is_balanced("()"));
}

TEST(simple_brackets) {
    EXPECT(is_balanced("[]"));
}

TEST(simple_braces) {
    EXPECT(is_balanced("{}"));
}

TEST(multiple_types_in_sequence) {
    EXPECT(is_balanced("()[]{}"));
}

TEST(nested) {
    EXPECT(is_balanced("{[]}"));
}

TEST(deeply_nested) {
    EXPECT(is_balanced("({[]})"));
}

TEST(mismatched_types) {
    EXPECT(!is_balanced("(]"));
}

TEST(mismatched_types_2) {
    EXPECT(!is_balanced("{)"));
}

TEST(wrong_nesting_order) {
    EXPECT(!is_balanced("([)]"));
}

TEST(only_openers) {
    EXPECT(!is_balanced("((("));
}

TEST(only_closers) {
    EXPECT(!is_balanced(")))"));
}

TEST(single_opener) {
    EXPECT(!is_balanced("("));
}

TEST(single_closer) {
    EXPECT(!is_balanced(")"));
}

TEST(close_before_open) {
    EXPECT(!is_balanced(")("));
}

TEST(complex_valid) {
    EXPECT(is_balanced("{[()()][(())]}"));
}

TEST(complex_invalid) {
    EXPECT(!is_balanced("{[()()][(()]}"));
}

TEST(repeated_pairs) {
    EXPECT(is_balanced("()()()()()"));
}

TEST(long_nested) {
    // 1000 levels deep: ((((....))))
    std::string s(1000, '(');
    s += std::string(1000, ')');
    EXPECT(is_balanced(s));
}

TEST(long_nested_with_mismatch) {
    // 999 '(' + 1 '[' + 999 ')' + 1 ']' — the ] hits a ( on the stack
    std::string s(999, '(');
    s += '[';
    s += std::string(999, ')');
    s += ']';
    EXPECT(!is_balanced(s));
}

int main() { return practice::run_all_tests(); }
