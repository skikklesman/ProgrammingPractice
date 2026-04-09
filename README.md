# Programming Practice

C++17 exercises for algorithms, bug-hunting, and performance optimization.

## Quick Start

```bash
cmake -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Exercises

| Exercise | Category | Difficulty |
|----------|----------|------------|
| [Two Sum](exercises/algorithms/01_two_sum/problem.md) | Algorithm | Easy |
| [String Splitter](exercises/bug_hunts/01_string_splitter/problem.md) | Bug Hunt | Easy |
| [Sum Matrix](exercises/performance/01_sum_matrix/problem.md) | Performance | Easy |

Each exercise has a `problem.md` with instructions. Edit `solution.cpp` and run the tests to check your work.

## Adding Exercises

Create a new directory under `exercises/<category>/` with `problem.md`, `solution.h`, `solution.cpp`, and `test.cpp`. CMake picks them up automatically.
