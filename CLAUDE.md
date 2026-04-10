# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Purpose

A C++17 exercise repo where the user practices algorithms, debugging, and performance optimization. Claude's role is to create exercises (with intentional bugs or slow code), add test cases, and assess the user's solutions — not to solve exercises for them. Each exercise is self-contained with a problem description, starter code, and tests. Always include many stress tests by default: edge cases, large inputs, boundary conditions, and diverse scenarios. Do not wait to be asked for thorough test coverage.

## Build Commands

The project uses CMake. Visual Studio 2022 Community is installed on this machine.

```bash
# Configure (from repo root)
cmake -B build

# Build everything
cmake --build build

# Run all tests
ctest --test-dir build --output-on-failure

# Build & run a single exercise (target name = path with "/" replaced by "_")
cmake --build build --target algorithms_01_two_sum
ctest --test-dir build -R algorithms_01_two_sum --output-on-failure
```

Target naming convention: `exercises/algorithms/01_two_sum/` becomes target `algorithms_01_two_sum`.

## Exercise Structure

Three categories under `exercises/`:
- **algorithms/** — implement a function from scratch (tests start failing)
- **bug_hunts/** — code compiles but has bugs; fix `solution.cpp` until tests pass
- **performance/** — code is correct but slow; optimize it (tests print timing via `ScopedTimer`)

Each exercise directory contains:
| File | Purpose |
|------|---------|
| `problem.md` | Problem statement and hints |
| `solution.h` | Function signature (do not modify) |
| `solution.cpp` | Starter/buggy code (edit this) |
| `test.cpp` | Tests (do not modify for the exercise) |

## Adding a New Exercise

1. Create `exercises/<category>/<NN_name>/` with the four files above.
2. CMake auto-discovers any `exercises/*/test.cpp` — no need to edit `CMakeLists.txt`.

## Shared Headers (`include/practice/`)

- **test.h** — zero-dependency test harness. Macros: `TEST(name)`, `EXPECT(expr)`, `EXPECT_EQ(a,b)`, `EXPECT_NEAR(a,b,tol)`. Entry point: `return practice::run_all_tests();`
- **timer.h** — `practice::ScopedTimer` RAII timer that prints elapsed time on scope exit. Used in performance exercises.
