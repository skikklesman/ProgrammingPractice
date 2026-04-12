# Performance: Count Pair Sums

`count_pair_sums()` takes a vector `v` and a target integer `t`, and returns
the number of unordered pairs `(i, j)` with `i < j` such that
`v[i] + v[j] == t`.

Example: `count_pair_sums({1, 2, 3, 4, 3}, 6)` → `2`
(pairs `(2,3)` at indices 2+3, and `(2,3)` at indices 3+4 — wait, let's be
precise: the pairs that sum to 6 are `(v[1]+v[4]=2+3)`? no, 2+3=5. The actual
pairs: `v[2]+v[3]=3+4=7`, `v[2]+v[4]=3+3=6` ✓, `v[3]+v[4]=4+3=7`,
`v[1]+v[3]=2+4=6` ✓. So 2 pairs.)

The provided implementation is **correct but slow** — it examines every pair,
giving O(n²) work.

## Goal

1. Run the tests — they will pass but also print timing information.
2. Optimize `count_pair_sums()` to run in expected O(n).
3. Do **not** change the function signature or the tests.

## Hint

For each element `v[i]`, the number of earlier elements equal to `t - v[i]`
is exactly how many new pairs ending at `i` exist. A hash map lets you look
that up in O(1).
