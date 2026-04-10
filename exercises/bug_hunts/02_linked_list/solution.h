#pragma once

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};

// Return true if the linked list starting at head contains a cycle.
bool has_cycle(ListNode* head);
