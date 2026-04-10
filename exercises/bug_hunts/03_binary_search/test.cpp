#include "practice/test.h"
#include "solution.h"
#include <numeric>

TEST(empty_vector) {
    EXPECT_EQ(binary_search({}, 5), -1);
}

TEST(single_element_found) {
    EXPECT_EQ(binary_search({7}, 7), 0);
}

TEST(single_element_not_found) {
    EXPECT_EQ(binary_search({7}, 3), -1);
}

TEST(two_elements_find_first) {
    EXPECT_EQ(binary_search({1, 3}, 1), 0);
}

TEST(two_elements_find_second) {
    EXPECT_EQ(binary_search({1, 3}, 3), 1);
}

TEST(two_elements_not_found) {
    EXPECT_EQ(binary_search({1, 3}, 2), -1);
}

TEST(find_at_beginning) {
    EXPECT_EQ(binary_search({1, 2, 3, 4, 5}, 1), 0);
}

TEST(find_at_end) {
    EXPECT_EQ(binary_search({1, 2, 3, 4, 5}, 5), 4);
}

TEST(find_in_middle) {
    EXPECT_EQ(binary_search({1, 2, 3, 4, 5}, 3), 2);
}

TEST(target_too_small) {
    EXPECT_EQ(binary_search({10, 20, 30}, 5), -1);
}

TEST(target_too_large) {
    EXPECT_EQ(binary_search({10, 20, 30}, 35), -1);
}

TEST(target_in_gap) {
    EXPECT_EQ(binary_search({10, 20, 30}, 15), -1);
}

TEST(negative_numbers) {
    EXPECT_EQ(binary_search({-10, -5, 0, 5, 10}, -5), 1);
}

TEST(negative_not_found) {
    EXPECT_EQ(binary_search({-10, -5, 0, 5, 10}, -3), -1);
}

TEST(duplicates_present) {
    auto result = binary_search({1, 2, 2, 2, 3}, 2);
    // Should find one of the 2s (index 1, 2, or 3)
    EXPECT(result >= 1 && result <= 3);
}

TEST(large_vector) {
    const int n = 100000;
    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 0);  // 0, 1, 2, ..., 99999

    EXPECT_EQ(binary_search(v, 0), 0);
    EXPECT_EQ(binary_search(v, 99999), 99999);
    EXPECT_EQ(binary_search(v, 50000), 50000);
    EXPECT_EQ(binary_search(v, 100000), -1);
}

int main() { return practice::run_all_tests(); }
