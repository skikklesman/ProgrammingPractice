#include "practice/test.h"
#include "practice/timer.h"
#include "solution.h"

TEST(zero) {
    EXPECT_EQ(build_sequence(0), "");
}

TEST(one) {
    EXPECT_EQ(build_sequence(1), "0");
}

TEST(five) {
    EXPECT_EQ(build_sequence(5), "0,1,2,3,4");
}

TEST(ten) {
    EXPECT_EQ(build_sequence(10), "0,1,2,3,4,5,6,7,8,9");
}

TEST(starts_and_ends_correctly) {
    std::string s = build_sequence(100);
    // Should start with "0,1,"
    EXPECT_EQ(s.substr(0, 4), "0,1,");
    // Should end with "99"
    EXPECT_EQ(s.substr(s.size() - 2), "99");
    // Should not start or end with a comma
    EXPECT(s.front() != ',');
    EXPECT(s.back() != ',');
}

TEST(large_correctness_and_timing) {
    std::string result;
    {
        practice::ScopedTimer t("build_sequence(100000)");
        result = build_sequence(100000);
    }
    // Spot-check: starts with "0,1,2,"
    EXPECT_EQ(result.substr(0, 6), "0,1,2,");
    // Ends with "99999"
    EXPECT_EQ(result.substr(result.size() - 5), "99999");
}

TEST(very_large_timing) {
    std::string result;
    {
        practice::ScopedTimer t("build_sequence(200000)");
        result = build_sequence(200000);
    }
    EXPECT_EQ(result.substr(result.size() - 6), "199999");
}

int main() { return practice::run_all_tests(); }
