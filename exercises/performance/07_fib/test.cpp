#include "practice/test.h"
#include "practice/timer.h"
#include "solution.h"

TEST(base_zero) { EXPECT_EQ(fib(0), 0LL); }
TEST(base_one)  { EXPECT_EQ(fib(1), 1LL); }

TEST(small_values) {
    EXPECT_EQ(fib(2), 1LL);
    EXPECT_EQ(fib(3), 2LL);
    EXPECT_EQ(fib(4), 3LL);
    EXPECT_EQ(fib(5), 5LL);
    EXPECT_EQ(fib(6), 8LL);
    EXPECT_EQ(fib(7), 13LL);
    EXPECT_EQ(fib(8), 21LL);
    EXPECT_EQ(fib(9), 34LL);
    EXPECT_EQ(fib(10), 55LL);
}

TEST(medium_values) {
    EXPECT_EQ(fib(15), 610LL);
    EXPECT_EQ(fib(20), 6765LL);
    EXPECT_EQ(fib(25), 75025LL);
    EXPECT_EQ(fib(30), 832040LL);
}

TEST(fib_35_timing) {
    long long r;
    {
        practice::ScopedTimer t("fib(35)");
        r = fib(35);
    }
    EXPECT_EQ(r, 9227465LL);
}

TEST(fib_38_timing) {
    long long r;
    {
        practice::ScopedTimer t("fib(38)");
        r = fib(38);
    }
    EXPECT_EQ(r, 39088169LL);
}

TEST(fib_40_timing) {
    long long r;
    {
        practice::ScopedTimer t("fib(40)");
        r = fib(40);
    }
    EXPECT_EQ(r, 102334155LL);
}

TEST(fib_42_timing) {
    long long r;
    {
        practice::ScopedTimer t("fib(42)");
        r = fib(42);
    }
    EXPECT_EQ(r, 267914296LL);
}

int main() { return practice::run_all_tests(); }
