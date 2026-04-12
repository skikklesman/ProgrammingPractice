#include "practice/test.h"
#include "practice/timer.h"
#include "solution.h"

TEST(n_zero)  { EXPECT_EQ(count_primes(0), 0); }
TEST(n_one)   { EXPECT_EQ(count_primes(1), 0); }
TEST(n_two)   { EXPECT_EQ(count_primes(2), 0); }
TEST(n_three) { EXPECT_EQ(count_primes(3), 1); }  // {2}
TEST(n_four)  { EXPECT_EQ(count_primes(4), 2); }  // {2, 3}
TEST(n_five)  { EXPECT_EQ(count_primes(5), 2); }  // still {2, 3}
TEST(n_six)   { EXPECT_EQ(count_primes(6), 3); }  // {2, 3, 5}

TEST(n_ten)  { EXPECT_EQ(count_primes(10), 4); }   // 2,3,5,7
TEST(n_twenty) { EXPECT_EQ(count_primes(20), 8); } // 2,3,5,7,11,13,17,19
TEST(n_hundred) { EXPECT_EQ(count_primes(100), 25); }

TEST(n_one_thousand) { EXPECT_EQ(count_primes(1000), 168); }
TEST(n_two_thousand) { EXPECT_EQ(count_primes(2000), 303); }

TEST(n_10000_timing) {
    int r;
    {
        practice::ScopedTimer t("count_primes(10000)");
        r = count_primes(10000);
    }
    EXPECT_EQ(r, 1229);
}

TEST(n_25000_timing) {
    int r;
    {
        practice::ScopedTimer t("count_primes(25000)");
        r = count_primes(25000);
    }
    EXPECT_EQ(r, 2762);
}

TEST(n_50000_timing) {
    int r;
    {
        practice::ScopedTimer t("count_primes(50000)");
        r = count_primes(50000);
    }
    EXPECT_EQ(r, 5133);
}

TEST(n_100000_timing) {
    int r;
    {
        practice::ScopedTimer t("count_primes(100000)");
        r = count_primes(100000);
    }
    EXPECT_EQ(r, 9592);
}

int main() { return practice::run_all_tests(); }
