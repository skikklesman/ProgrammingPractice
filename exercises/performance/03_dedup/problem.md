# Performance: Remove Duplicates

`dedup()` takes a vector of integers and returns a new vector with duplicates
removed, preserving the **first occurrence order**.

The provided implementation is correct but uses a nested loop to check for
duplicates — O(n²) in the worst case.

## Example

```
Input:  {3, 1, 4, 1, 5, 9, 2, 6, 5, 3}
Output: {3, 1, 4, 5, 9, 2, 6}
```

## Goal

1. Run the tests to see the timing on large inputs.
2. Optimize `dedup()` so it runs significantly faster.
3. Do **not** change the function signature or the tests.
4. The output order must match the order of first appearances.

## Hint

Think about what data structure gives you O(1) lookups for "have I seen this
value before?"
