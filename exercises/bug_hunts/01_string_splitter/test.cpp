#include "practice/test.h"
#include "solution.h"

TEST(simple_split) {
    auto result = split("a,b,c", ',');
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");
    EXPECT_EQ(result[2], "c");
}

TEST(empty_input) {
    auto result = split("", ',');
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], "");
}

TEST(no_delimiter_present) {
    auto result = split("hello", ',');
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], "hello");
}

TEST(consecutive_delimiters) {
    auto result = split("a,,b", ',');
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "");
    EXPECT_EQ(result[2], "b");
}

TEST(trailing_delimiter) {
    auto result = split("a,b,", ',');
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");
    EXPECT_EQ(result[2], "");
}

TEST(leading_delimiter) {
    auto result = split(",a,b", ',');
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "");
    EXPECT_EQ(result[1], "a");
    EXPECT_EQ(result[2], "b");
}

TEST(only_delimiters) {
    auto result = split(",,,", ',');
    EXPECT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], "");
    EXPECT_EQ(result[1], "");
    EXPECT_EQ(result[2], "");
    EXPECT_EQ(result[3], "");
}

TEST(single_delimiter) {
    auto result = split(",", ',');
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "");
    EXPECT_EQ(result[1], "");
}

TEST(single_character_no_delim) {
    auto result = split("x", ',');
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], "x");
}

TEST(different_delimiter) {
    auto result = split("one:two:three", ':');
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "one");
    EXPECT_EQ(result[1], "two");
    EXPECT_EQ(result[2], "three");
}

TEST(space_delimiter) {
    auto result = split("hello world foo", ' ');
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(result[1], "world");
    EXPECT_EQ(result[2], "foo");
}

TEST(delimiter_is_in_tokens_as_other_char) {
    // Splitting by ':' — commas are just normal characters
    auto result = split("a,b:c,d", ':');
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "a,b");
    EXPECT_EQ(result[1], "c,d");
}

TEST(many_consecutive_delimiters) {
    auto result = split("a,,,,,b", ',');
    EXPECT_EQ(result.size(), 6u);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "");
    EXPECT_EQ(result[2], "");
    EXPECT_EQ(result[3], "");
    EXPECT_EQ(result[4], "");
    EXPECT_EQ(result[5], "b");
}

TEST(long_tokens) {
    auto result = split("abcdefghij,klmnopqrst,uvwxyz", ',');
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "abcdefghij");
    EXPECT_EQ(result[1], "klmnopqrst");
    EXPECT_EQ(result[2], "uvwxyz");
}

TEST(leading_and_trailing_delimiters) {
    auto result = split(",a,b,", ',');
    EXPECT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], "");
    EXPECT_EQ(result[1], "a");
    EXPECT_EQ(result[2], "b");
    EXPECT_EQ(result[3], "");
}

TEST(whitespace_tokens) {
    auto result = split(" , , ", ',');
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], " ");
    EXPECT_EQ(result[1], " ");
    EXPECT_EQ(result[2], " ");
}

int main() { return practice::run_all_tests(); }
