# Bug Hunt: Linked List Cycle Detection

A singly-linked list may or may not contain a cycle (a node whose `next`
pointer leads back to an earlier node). `has_cycle()` is supposed to return
`true` if a cycle exists, `false` otherwise.

The implementation uses Floyd's tortoise-and-hare algorithm (two pointers
moving at different speeds), but it has **bugs** that cause it to crash or
return wrong results.

## Goal

Run the tests, observe the failures or crashes, then **fix the bugs** in
`solution.cpp` so that all tests pass.
