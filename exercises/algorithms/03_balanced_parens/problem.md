# Balanced Parentheses

Given a string containing only the characters `(`, `)`, `{`, `}`, `[`, `]`,
determine if the input string has balanced brackets.

A string is balanced when:
- Every opening bracket has a matching closing bracket of the same type.
- Brackets are closed in the correct order.

## Examples

```
"()"       → true
"()[]{}"   → true
"(]"       → false
"([)]"     → false
"{[]}"     → true
```

## Goal

Implement `is_balanced()` in **solution.cpp** so that all tests pass.
Think about which data structure lets you track what's "currently open."
