# Bug Hunt: Transactional Key-Value Store

A `KVStore` class provides an in-memory key-value store (string keys, int values)
with **nested transaction** support:

| Method | Behaviour |
|--------|-----------|
| `put(key, value)` | Insert or update a key |
| `get(key)` | Return the value, or `nullopt` if missing |
| `remove(key)` | Erase a key; return `true` if it existed |
| `begin()` | Open a new transaction (nestable) |
| `commit()` | Commit the innermost transaction; return `false` if none open |
| `rollback()` | Undo everything in the innermost transaction; return `false` if none open |
| `range_query(lo, hi)` | All pairs with keys in **[lo, hi]** (inclusive), sorted by key |
| `count()` | Number of stored keys |

### Transaction semantics

* `rollback()` must perfectly undo every `put` and `remove` since the matching
  `begin()` — restoring previous values, re-inserting removed keys, and
  removing keys that were newly added.
* Nested transactions: committing an inner transaction makes its changes
  durable within the **outer** transaction (not globally). A subsequent
  rollback of the outer transaction must still undo the inner changes.

### Phase 1 — Fix the bugs

The implementation compiles and appears reasonable, but it has **three
distinct bugs** that cause incorrect results. Run the tests, read the
failures, and fix `solution.cpp` until every test passes.

Hints (read only if stuck):
1. One bug is in a mutating operation that "forgets" to leave a trail.
2. One bug is in how transaction boundaries interact when nested.
3. One bug is an off-by-one in a query boundary.

### Phase 2 — Optimise

After all tests pass, look at the `[TIMER]` output from the stress tests.
The implementation uses a `std::vector` of pairs with linear scans for
every operation. For large data sets this is painfully slow.

Redesign the internals so that:
* `put` / `get` / `remove` are **O(log n)**
* `range_query` is **O(log n + k)** where *k* is the result size
* The transaction undo mechanism still works correctly

You **may** change private members in `solution.h`; the public interface
must stay the same.
