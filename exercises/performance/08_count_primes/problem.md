# Performance: Count Primes

`count_primes(n)` returns the number of prime numbers strictly less than `n`.
For example, `count_primes(10) == 4` because the primes below 10 are
`{2, 3, 5, 7}`.

The provided implementation is **correct but slow** — it checks each
candidate by trial division up to the number itself, which is far more work
than necessary.

## Goal

1. Run the tests — small cases pass quickly, but the large-n timing tests
   are painfully slow with the current implementation.
2. Optimize `count_primes()` so it can handle `n` in the millions in a
   fraction of a second.
3. Do **not** change the function signature or the tests.

## Hints

There are two independent improvements:

1. **Trial division smarter** — you only need to test divisors up to the
   square root of the candidate, and you can skip even numbers after 2.
2. **Sieve of Eratosthenes** — allocate a `std::vector<bool>` (or
   `std::vector<char>`) of size `n` and mark multiples of each prime as
   composite. This is O(n log log n) overall and typically the fastest
   approach for counting primes below n.
