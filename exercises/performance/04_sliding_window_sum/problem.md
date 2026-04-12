# Performance: Sliding Window Sum

`window_sums()` takes a vector `v` and a window size `k`, and returns a vector
where the i-th entry is the sum of `v[i..i+k-1]`. The output has size
`v.size() - k + 1` (empty if `k > v.size()`).

Example: `window_sums({1,2,3,4,5}, 3)` → `{6, 9, 12}`

The provided implementation is **correct but slow**: for each window it
recomputes the sum from scratch, giving O(n·k) total work.

## Goal

1. Run the tests — they will pass but also print timing information.
2. Optimize `window_sums()` so it runs in O(n).
3. Do **not** change the function signature or the tests.

## Hint

When the window slides by one position, only one element leaves and one
element enters. You don't have to re-add the rest.
