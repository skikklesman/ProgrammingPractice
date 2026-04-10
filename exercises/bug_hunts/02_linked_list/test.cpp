#include "practice/test.h"
#include "solution.h"
#include <vector>

// Helper: build a list from values, optionally creating a cycle.
// cycle_pos = -1 means no cycle.
// cycle_pos = k means the tail's next points to node at index k.
static std::vector<ListNode> make_list(const std::vector<int>& vals, int cycle_pos = -1) {
    std::vector<ListNode> nodes;
    nodes.reserve(vals.size());
    for (int v : vals) nodes.emplace_back(v);
    for (size_t i = 0; i + 1 < nodes.size(); ++i)
        nodes[i].next = &nodes[i + 1];
    if (cycle_pos >= 0 && !nodes.empty())
        nodes.back().next = &nodes[cycle_pos];
    return nodes;
}

TEST(empty_list) {
    EXPECT(!has_cycle(nullptr));
}

TEST(single_node_no_cycle) {
    ListNode n(1);
    EXPECT(!has_cycle(&n));
}

TEST(single_node_self_cycle) {
    ListNode n(1);
    n.next = &n;
    EXPECT(has_cycle(&n));
}

TEST(two_nodes_no_cycle) {
    auto nodes = make_list({1, 2});
    EXPECT(!has_cycle(&nodes[0]));
}

TEST(two_nodes_cycle) {
    auto nodes = make_list({1, 2}, 0);
    EXPECT(has_cycle(&nodes[0]));
}

TEST(cycle_at_head) {
    auto nodes = make_list({1, 2, 3, 4}, 0);
    EXPECT(has_cycle(&nodes[0]));
}

TEST(cycle_in_middle) {
    auto nodes = make_list({1, 2, 3, 4, 5}, 2);
    // 5 → 3 → 4 → 5 → 3 → ...
    EXPECT(has_cycle(&nodes[0]));
}

TEST(tail_self_cycle) {
    auto nodes = make_list({1, 2, 3});
    nodes[2].next = &nodes[2];  // tail points to itself
    EXPECT(has_cycle(&nodes[0]));
}

TEST(long_list_no_cycle) {
    auto nodes = make_list({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    EXPECT(!has_cycle(&nodes[0]));
}

TEST(long_list_late_cycle) {
    auto nodes = make_list({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 7);
    // 10 → 8 → 9 → 10 → 8 → ...
    EXPECT(has_cycle(&nodes[0]));
}

int main() { return practice::run_all_tests(); }
