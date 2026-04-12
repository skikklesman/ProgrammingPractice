#include "solution.h"

// Count the number of primes strictly less than n.
//
// Tests cover:
//   - Edge cases: n = 0, 1, 2 → 0
//   - Small n with hand-verified counts (n = 10, 20, 100)
//   - Medium n (n = 1000, 2000) with known counts
//   - Timing tests at n = 5000, 10000, 15000, 20000 — the slow version
//     spends most of its time in the inner division loop.
//
// The implementation below has two inefficiencies:
//   1. It tries every divisor from 2 up to k - 1 — you only need up to sqrt(k).
//   2. It doesn't skip even candidates after 2.
// Fixing just (1) is a huge speedup. For the big timing tests, replace the
// whole thing with a sieve of Eratosthenes.
int count_primes(int n) {
    if (n < 3) return 0;
    int count = 1;  // account for 2
    for (int k = 3; k < n; ++k) {
        bool prime = true;
        for (int d = 2; d < k; ++d) {
            if (k % d == 0) {
                prime = false;
                break;
            }
        }
        if (prime) ++count;
    }
    return count;
}
