# Performance: String Building

`build_sequence()` builds a string of comma-separated integers:
`"0,1,2,3,...,n-1"`.

The provided implementation is correct but uses naive string concatenation
inside a loop, which causes **quadratic** runtime due to repeated copying.

## Goal

1. Run the tests to see the timing on the large input.
2. Optimize `build_sequence()` to run significantly faster.
3. Do **not** change the function signature or the tests.

## Hints

- `std::string::reserve()` pre-allocates capacity to avoid reallocations.
- `std::ostringstream` or `std::to_string()` with `+=` on a reserved string
  are both good approaches.
- Think about how many times the string's buffer gets copied when you use `+`
  to build it up character by character.
