# Performance: Fibonacci

`fib(n)` returns the n-th Fibonacci number, where:

```
fib(0) = 0
fib(1) = 1
fib(n) = fib(n-1) + fib(n-2)
```

The provided implementation is **correct but slow** — it recursively calls
itself twice, recomputing the same values exponentially many times. Even
`fib(40)` is noticeably slow.

The results fit in `long long` for all tested `n` (the largest is `n = 90`,
which gives `2880067194370816120`).

## Goal

1. Run the tests — the smaller cases pass quickly, but the large-n tests
   will take a long time with the provided implementation.
2. Optimize `fib()` so it runs in O(n) (or better) with O(1) extra space.
3. Do **not** change the function signature or the tests.

## Hint

You don't need recursion at all. Keep just the last two values and iterate.
