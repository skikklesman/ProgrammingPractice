#include "solution.h"

// Detect whether a singly-linked list contains a cycle using Floyd's
// tortoise-and-hare algorithm: one pointer moves 1 step, the other moves
// 2 steps. If they ever meet, there's a cycle.
//
// Tests cover:
//   - Empty list (nullptr)
//   - Single node, no cycle
//   - Single node pointing to itself
//   - Two nodes, no cycle
//   - Two nodes forming a cycle
//   - Cycle starting at the head
//   - Cycle starting in the middle
//   - Cycle at the tail (last node points to itself)
//   - Long list with no cycle
//   - Long list with a late cycle
//
// The code below attempts Floyd's algorithm but has bug(s). Find and fix them.
bool has_cycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}
