# Performance: Range Sum Queries

`range_sums()` takes a vector `v` and a list of queries. Each query is a
`(l, r)` pair; the answer for that query is the sum of `v[l..r]` inclusive.
The function returns one answer per query, in order.

You can assume `0 <= l <= r < v.size()` for every query.

The provided implementation is **correct but slow** — it sums the range
from scratch for each query, giving O(q·n) total work.

## Goal

1. Run the tests — they will pass but also print timing information.
2. Optimize `range_sums()` so that answering q queries over a vector of
   size n takes O(n + q) total.
3. Do **not** change the function signature or the tests.

## Hint

Precompute something once, then answer each query in O(1). Think about
cumulative sums: if `P[i] = v[0] + v[1] + ... + v[i-1]`, then
`sum(v[l..r]) = P[r+1] - P[l]`.
