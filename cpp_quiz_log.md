# C++ Knowledge Quiz Log

## Q1
**Q:** What is the difference between `stack` and `heap` memory allocation in C++? When does each get used?

**A:** Stack = local variables, scoped lifetime, freed on scope exit. Heap = `new`/dynamic allocation, larger, must be manually freed (or use smart pointers). Failure to free = memory leak.

**Result:** Correct. Minor additions: heap is also used implicitly by STL containers (`vector`, `string`, etc.), and modern C++ prefers smart pointers (`unique_ptr`, `shared_ptr`) over raw `new`/`delete` via RAII.

---

## Q2
**Q:** What does `const` mean when applied in these three positions on a member function: `const int* foo(const int& x) const;`?

**A:** Got `const int&` correct (can't modify x). Got trailing `const` mostly right but too broad — it only protects member variables, not all outside data. Got `const int*` backwards — it means the pointed-to int is const, not the pointer. `const` applies to the thing to its left (or right if nothing is on the left).

**Result:** Partial. Key correction: `const int*` = pointer to const int (value is read-only, pointer can move). `int* const` = const pointer (pointer is fixed, value can change). Trailing `const` = promise about `this` object's members only, not about side effects.

---

## Q3
**Q:** What is the difference between `std::move` and copying? When would you use `std::move`?

**A:** Didn't know.

**Result:** Learning opportunity. Copying duplicates data; moving transfers ownership of internal resources (e.g., a vector move copies the pointer, not the elements). `std::move` is a cast that marks an object as "moveable." Use it when you're done with the source. The compiler often moves automatically for temporaries and return values.

---

## Q4
**Q:** What happens if you dereference a `nullptr`? And what is the difference between `nullptr`, `NULL`, and `0` in C++?

**A:** Partial. Knew nullptr was a distinct type and NULL/0 are related, but said "null exception" — C++ has no such thing.

**Result:** Dereferencing nullptr is **undefined behavior** (usually a segfault, no exception). `0` and `NULL` are integers; `nullptr` (C++11) is type `std::nullptr_t`, making it unambiguous in overload resolution. Always use `nullptr` in modern C++.

---

## Q5
**Q:** What is a virtual function, and why would you declare a destructor `virtual`?

**A:** Correct on both parts. Virtual = runtime dispatch via vtable, allowing child to override parent behavior through a base pointer. Virtual destructor ensures `delete base_ptr` calls the derived destructor first, preventing resource leaks.

**Result:** Correct. Rule of thumb: if a class has any virtual functions, its destructor should be virtual.

---

## Q6
**Q:** What is the difference between `struct` and `class` in C++?

**A:** Correct. Default access: `struct` = public, `class` = private. Same applies to default inheritance. Otherwise identical.

**Result:** Correct.

---

## Q7
**Q:** What is RAII, and how does it relate to resource management in C++?

**A:** Correct core concept — tie resource lifetime to stack scope via constructor/destructor. Broadening: applies to any resource (files, locks, connections), not just memory. Exception-safe because destructors are guaranteed to run on scope exit.

**Result:** Correct. Already used this pattern via `ScopedTimer` in performance exercises.

---

## Q8
**Q:** What does `inline` do, and does it actually force the compiler to inline a function?

**A:** Correctly described what inlining is at the assembly level, but attributed it to the keyword. `inline` actually controls linkage (allows multiple definitions across translation units), not optimization. The compiler decides what to inline on its own regardless of the keyword.

**Result:** Incorrect about the keyword, correct about the concept. `inline` = linkage rule. Actual inlining = compiler heuristic.

---

## Q9
**Q:** What is the difference between `emplace_back` and `push_back` on a `std::vector`?

**A:** Incorrect — confused it with capacity/allocation behavior. Both handle reallocation identically.

**Result:** `push_back` takes a constructed object and copies/moves it in. `emplace_back` takes constructor *arguments* and constructs the object directly in the vector's memory, avoiding any temporary. For simple types, no difference. For complex types, `emplace_back` can skip a copy/move.

---

## Q10
**Q:** What is a dangling pointer, and give an example of how one can occur?

**A:** Correct. Pointer to freed/out-of-scope memory. Gave two valid examples: shared pointer after `delete`, and pointer to stack variable after scope exit. Additional case: iterator/pointer invalidation from vector reallocation.

**Result:** Correct.

---

## Q11
**Q:** What are templates in C++, and what does "template instantiation" mean?

**A:** Correct. Compile-time code generation specialized per type. Each usage instantiates a type-specific version. Note: definitions must be in headers since the compiler needs the full code at instantiation, which is why heavy template use slows compile times.

**Result:** Correct.

---

## Q12
**Q:** What is the difference between a `reference` and a `pointer` in C++? When would you choose one over the other?

**A:** Correct. Reference = non-null alias, always bound, can't reseat. Pointer = can be null, can reseat. Additional note: assigning to a reference modifies the original, doesn't rebind. Prefer references by default; use pointers when null or reseating is needed.

**Result:** Correct.

---

## Q13
**Q:** What is undefined behavior (UB) in C++? Why is it more dangerous than just "it crashes"?

**A:** Partially correct — identified hidden bugs and platform/compiler variance. Missed the key insight: the compiler **assumes UB can't happen** and optimizes accordingly, which can remove safety checks and produce logically impossible behavior. Can work in debug but break in release.

**Result:** Partial. The compiler-assumes-no-UB aspect is the most dangerous part.

---

## Q14
**Q:** What is the Rule of Three (or Rule of Five) in C++?

**A:** Didn't know.

**Result:** Learning opportunity. If a class needs a custom destructor, copy constructor, or copy assignment, it needs all three (Rule of Three). C++11 adds move constructor + move assignment (Rule of Five). Modern best practice: use RAII types so you need none of them (Rule of Zero).

---

## Q15
**Q:** What does `static` mean in these three contexts: a local variable inside a function, a member variable of a class, and a free function in a `.cpp` file?

**A:** Correct on all three. Minor correction: static locals are initialized on first call, not at startup (thread-safe since C++11). Modern alternative to `static` free functions: anonymous namespaces.

**Result:** Correct.

---

## Q16
**Q:** What is a lambda in C++, and what does the capture list `[&]` vs `[=]` mean?

**A:** Knew lambdas are inline functions that use surrounding scope variables. Didn't know capture syntax.

**Result:** Partial. `[=]` = capture by value (snapshot), `[&]` = capture by reference (live). Can mix per-variable: `[x, &y]`. Use `[&]` for immediate lambdas, `[=]` when the lambda may outlive the scope.

