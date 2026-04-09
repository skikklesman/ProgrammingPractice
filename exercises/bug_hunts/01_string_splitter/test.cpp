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

int main() { return practice::run_all_tests(); }
