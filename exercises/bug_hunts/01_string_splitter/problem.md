# Bug Hunt: String Splitter

The function `split()` is supposed to split a string by a delimiter and return
a vector of tokens. For example:

```
split("a,b,c", ',')  →  {"a", "b", "c"}
```

The implementation compiles, but **produces wrong results** in several cases.

## Goal

Read the tests, run them, observe the failures, then **fix the bugs** in
`solution.cpp` so that all tests pass.
