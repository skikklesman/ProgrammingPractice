#include "solution.h"
#include <practice/test.h>
#include <practice/timer.h>

#include <algorithm>
#include <map>
#include <random>
#include <string>

// ===================================================================
//  Basic operations
// ===================================================================

TEST(put_and_get) {
    KVStore s;
    s.put("hello", 42);
    EXPECT_EQ(s.get("hello").value(), 42);
}

TEST(get_missing_key) {
    KVStore s;
    EXPECT(!s.get("nope").has_value());
}

TEST(put_overwrites_value) {
    KVStore s;
    s.put("key", 1);
    s.put("key", 2);
    EXPECT_EQ(s.get("key").value(), 2);
    EXPECT_EQ(s.count(), size_t(1));
}

TEST(remove_existing_key) {
    KVStore s;
    s.put("a", 1);
    EXPECT(s.remove("a"));
    EXPECT(!s.get("a").has_value());
    EXPECT_EQ(s.count(), size_t(0));
}

TEST(remove_nonexistent_key) {
    KVStore s;
    EXPECT(!s.remove("ghost"));
}

TEST(count_tracks_inserts_and_removes) {
    KVStore s;
    EXPECT_EQ(s.count(), size_t(0));
    s.put("a", 1);
    s.put("b", 2);
    s.put("c", 3);
    EXPECT_EQ(s.count(), size_t(3));
    s.remove("b");
    EXPECT_EQ(s.count(), size_t(2));
}

// ===================================================================
//  Range queries
// ===================================================================

TEST(range_query_basic) {
    KVStore s;
    s.put("banana", 2);
    s.put("apple", 1);
    s.put("cherry", 3);
    s.put("date", 4);

    auto r = s.range_query("banana", "cherry");
    EXPECT_EQ(r.size(), size_t(2));
    if (r.size() >= 2) {
        EXPECT_EQ(r[0].first, std::string("banana"));
        EXPECT_EQ(r[1].first, std::string("cherry"));
    }
}

TEST(range_query_inclusive_upper_bound) {
    KVStore s;
    s.put("a", 1);
    s.put("b", 2);
    s.put("c", 3);

    auto r = s.range_query("a", "c");
    EXPECT_EQ(r.size(), size_t(3));
    bool found_c = false;
    for (auto& [k, v] : r) if (k == "c") found_c = true;
    EXPECT(found_c);
}

TEST(range_query_single_key_equals_both_bounds) {
    KVStore s;
    s.put("m", 100);
    auto r = s.range_query("m", "m");
    EXPECT_EQ(r.size(), size_t(1));
    if (!r.empty()) EXPECT_EQ(r[0].second, 100);
}

TEST(range_query_no_matches) {
    KVStore s;
    s.put("a", 1);
    s.put("z", 26);
    auto r = s.range_query("m", "n");
    EXPECT_EQ(r.size(), size_t(0));
}

TEST(range_query_returns_sorted) {
    KVStore s;
    s.put("delta", 4);
    s.put("alpha", 1);
    s.put("charlie", 3);
    s.put("bravo", 2);
    auto r = s.range_query("alpha", "delta");
    EXPECT_EQ(r.size(), size_t(4));
    for (size_t i = 1; i < r.size(); ++i)
        EXPECT(r[i - 1].first <= r[i].first);
}

TEST(range_query_upper_bound_not_present) {
    KVStore s;
    s.put("a", 1);
    s.put("c", 3);
    s.put("e", 5);
    // "d" doesn't exist but the range [a,d] should still include a and c
    auto r = s.range_query("a", "d");
    EXPECT_EQ(r.size(), size_t(2));
}

// ===================================================================
//  Transactions — basic commit / rollback
// ===================================================================

TEST(commit_persists_changes) {
    KVStore s;
    s.put("x", 1);
    s.begin();
    s.put("x", 2);
    EXPECT(s.commit());
    EXPECT_EQ(s.get("x").value(), 2);
}

TEST(rollback_restores_overwritten_value) {
    KVStore s;
    s.put("x", 1);
    s.begin();
    s.put("x", 999);
    s.rollback();
    EXPECT_EQ(s.get("x").value(), 1);
}

TEST(rollback_removes_newly_added_key) {
    KVStore s;
    s.begin();
    s.put("fresh", 42);
    EXPECT(s.get("fresh").has_value());
    s.rollback();
    EXPECT(!s.get("fresh").has_value());
}

TEST(rollback_restores_removed_key) {
    KVStore s;
    s.put("victim", 7);
    s.begin();
    s.remove("victim");
    EXPECT(!s.get("victim").has_value());
    s.rollback();
    // "victim" must reappear with its original value.
    EXPECT(s.get("victim").has_value());
    EXPECT_EQ(s.get("victim").value(), 7);
}

TEST(rollback_restores_removed_then_readded_key) {
    KVStore s;
    s.put("k", 10);
    s.begin();
    s.remove("k");
    s.put("k", 20);
    s.rollback();
    EXPECT_EQ(s.get("k").value(), 10);
}

TEST(commit_without_transaction_returns_false) {
    KVStore s;
    EXPECT(!s.commit());
}

TEST(rollback_without_transaction_returns_false) {
    KVStore s;
    EXPECT(!s.rollback());
}

TEST(transaction_multiple_keys_rollback) {
    KVStore s;
    s.put("a", 1); s.put("b", 2); s.put("c", 3);
    s.begin();
    s.put("a", 10);
    s.put("b", 20);
    s.remove("c");
    s.put("d", 40);
    s.rollback();
    EXPECT_EQ(s.get("a").value(), 1);
    EXPECT_EQ(s.get("b").value(), 2);
    EXPECT_EQ(s.get("c").value(), 3);
    EXPECT(!s.get("d").has_value());
}

TEST(remove_multiple_keys_in_transaction_rollback) {
    KVStore s;
    s.put("x", 10); s.put("y", 20); s.put("z", 30);
    s.begin();
    s.remove("x");
    s.remove("y");
    s.remove("z");
    EXPECT_EQ(s.count(), size_t(0));
    s.rollback();
    EXPECT_EQ(s.count(), size_t(3));
    EXPECT_EQ(s.get("x").value(), 10);
    EXPECT_EQ(s.get("y").value(), 20);
    EXPECT_EQ(s.get("z").value(), 30);
}

// ===================================================================
//  Nested transactions
// ===================================================================

TEST(nested_inner_commit_outer_rollback) {
    KVStore s;
    s.put("x", 1);
    s.begin();             // outer
    s.begin();             // inner
    s.put("x", 3);
    s.commit();            // inner — merges into outer
    EXPECT_EQ(s.get("x").value(), 3);
    s.rollback();          // outer — must undo the inner change too
    EXPECT_EQ(s.get("x").value(), 1);
}

TEST(nested_inner_commit_outer_commit) {
    KVStore s;
    s.put("a", 1);
    s.begin();
    s.put("a", 2);
    s.begin();
    s.put("a", 3);
    s.commit();
    s.commit();
    EXPECT_EQ(s.get("a").value(), 3);
}

TEST(nested_inner_rollback_outer_commit) {
    KVStore s;
    s.put("x", 1);
    s.begin();
    s.put("x", 2);
    s.begin();
    s.put("x", 3);
    s.rollback();          // inner — back to 2
    EXPECT_EQ(s.get("x").value(), 2);
    s.commit();            // outer
    EXPECT_EQ(s.get("x").value(), 2);
}

TEST(nested_new_key_inner_commit_outer_rollback) {
    KVStore s;
    s.begin();
    s.begin();
    s.put("brand_new", 99);
    s.commit();
    EXPECT(s.get("brand_new").has_value());
    s.rollback();
    EXPECT(!s.get("brand_new").has_value());
}

TEST(triple_nested_all_commit_then_outer_rollback) {
    KVStore s;
    s.put("k", 0);
    s.begin();              // L1
    s.begin();              // L2
    s.put("k", 2);
    s.begin();              // L3
    s.put("k", 3);
    s.commit();             // L3
    s.commit();             // L2
    EXPECT_EQ(s.get("k").value(), 3);
    s.rollback();           // L1 — must restore k to 0
    EXPECT_EQ(s.get("k").value(), 0);
}

TEST(nested_remove_inner_commit_outer_rollback) {
    KVStore s;
    s.put("alive", 42);
    s.begin();              // outer
    s.begin();              // inner
    s.remove("alive");
    s.commit();             // inner
    EXPECT(!s.get("alive").has_value());
    s.rollback();           // outer — "alive" must come back
    EXPECT(s.get("alive").has_value());
    EXPECT_EQ(s.get("alive").value(), 42);
}

TEST(nested_mixed_operations_rollback) {
    KVStore s;
    s.put("a", 1); s.put("b", 2);
    s.begin();
    s.put("a", 10);
    s.begin();
    s.remove("a");
    s.put("c", 30);
    s.commit();             // inner
    EXPECT(!s.get("a").has_value());
    EXPECT_EQ(s.get("c").value(), 30);
    s.rollback();           // outer — restore a=1, b=2, remove c
    EXPECT_EQ(s.get("a").value(), 1);
    EXPECT_EQ(s.get("b").value(), 2);
    EXPECT(!s.get("c").has_value());
}

TEST(deeply_nested_5_levels) {
    KVStore s;
    s.put("v", 0);
    for (int d = 1; d <= 5; ++d) {
        s.begin();
        s.put("v", d);
    }
    EXPECT_EQ(s.get("v").value(), 5);

    // Commit levels 5-2 into level 1
    for (int d = 0; d < 4; ++d)
        s.commit();
    // Rollback level 1
    s.rollback();
    EXPECT_EQ(s.get("v").value(), 0);
}

// ===================================================================
//  Edge cases
// ===================================================================

TEST(range_query_after_remove) {
    KVStore s;
    s.put("a", 1); s.put("b", 2); s.put("c", 3);
    s.remove("b");
    auto r = s.range_query("a", "c");
    EXPECT_EQ(r.size(), size_t(2));
}

TEST(range_query_inside_transaction) {
    KVStore s;
    s.put("a", 1); s.put("b", 2); s.put("c", 3);
    s.begin();
    s.remove("b");
    s.put("d", 4);
    auto r = s.range_query("a", "d");
    EXPECT_EQ(r.size(), size_t(3)); // a, c, d
    s.rollback();
    // After rollback: a, b, c exist; d is gone.
    r = s.range_query("a", "c");
    EXPECT_EQ(r.size(), size_t(3));
    EXPECT(!s.get("d").has_value());
}

TEST(put_same_key_many_times_in_transaction) {
    KVStore s;
    s.put("x", 0);
    s.begin();
    for (int i = 1; i <= 100; ++i)
        s.put("x", i);
    EXPECT_EQ(s.get("x").value(), 100);
    s.rollback();
    EXPECT_EQ(s.get("x").value(), 0);
}

TEST(empty_transaction_commit) {
    KVStore s;
    s.put("x", 1);
    s.begin();
    s.commit();
    EXPECT_EQ(s.get("x").value(), 1);
}

TEST(empty_transaction_rollback) {
    KVStore s;
    s.put("x", 1);
    s.begin();
    s.rollback();
    EXPECT_EQ(s.get("x").value(), 1);
}

// ===================================================================
//  Stress tests (also check performance via ScopedTimer)
// ===================================================================

TEST(stress_insert_and_lookup) {
    KVStore s;
    const int N = 10000;
    {
        practice::ScopedTimer t("insert " + std::to_string(N) + " keys");
        for (int i = 0; i < N; ++i)
            s.put("key_" + std::to_string(i), i);
    }
    EXPECT_EQ(s.count(), size_t(N));
    {
        practice::ScopedTimer t("lookup " + std::to_string(N) + " keys");
        for (int i = 0; i < N; ++i)
            EXPECT_EQ(s.get("key_" + std::to_string(i)).value(), i);
    }
}

TEST(stress_range_query) {
    KVStore s;
    const int N = 10000;
    for (int i = 0; i < N; ++i) {
        char buf[20];
        snprintf(buf, sizeof(buf), "key_%05d", i);
        s.put(buf, i);
    }
    {
        practice::ScopedTimer t("range_query 50% of " + std::to_string(N));
        auto r = s.range_query("key_02500", "key_07500");
        EXPECT_EQ(r.size(), size_t(5001));
        for (size_t i = 1; i < r.size(); ++i)
            EXPECT(r[i - 1].first < r[i].first);
    }
}

TEST(stress_repeated_range_queries) {
    KVStore s;
    const int N = 5000;
    for (int i = 0; i < N; ++i) {
        char buf[16];
        snprintf(buf, sizeof(buf), "k%05d", i);
        s.put(buf, i);
    }
    {
        practice::ScopedTimer t("200 range queries over " + std::to_string(N));
        for (int q = 0; q < 200; ++q) {
            char lo[16], hi[16];
            snprintf(lo, sizeof(lo), "k%05d", q * 20);
            snprintf(hi, sizeof(hi), "k%05d", q * 20 + 100);
            auto r = s.range_query(lo, hi);
            EXPECT(r.size() > 0);
        }
    }
}

TEST(stress_transaction_rollback) {
    KVStore s;
    const int N = 3000;
    for (int i = 0; i < N; ++i)
        s.put("pre_" + std::to_string(i), i);

    s.begin();
    for (int i = 0; i < N; ++i) {
        s.put("pre_" + std::to_string(i), i * 100);
        s.put("new_" + std::to_string(i), i);
    }
    {
        practice::ScopedTimer t("rollback " + std::to_string(N * 2) + " ops");
        s.rollback();
    }
    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(s.get("pre_" + std::to_string(i)).value(), i);
        EXPECT(!s.get("new_" + std::to_string(i)).has_value());
    }
    EXPECT_EQ(s.count(), size_t(N));
}

TEST(stress_remove_in_transaction_rollback) {
    KVStore s;
    const int N = 1000;
    for (int i = 0; i < N; ++i)
        s.put("r_" + std::to_string(i), i);

    s.begin();
    {
        practice::ScopedTimer t("remove " + std::to_string(N) + " keys in txn");
        for (int i = 0; i < N; ++i)
            s.remove("r_" + std::to_string(i));
    }
    EXPECT_EQ(s.count(), size_t(0));
    s.rollback();
    EXPECT_EQ(s.count(), size_t(N));
    for (int i = 0; i < N; ++i)
        EXPECT_EQ(s.get("r_" + std::to_string(i)).value(), i);
}

TEST(stress_nested_commit_then_rollback) {
    KVStore s;
    const int N = 500;
    for (int i = 0; i < N; ++i)
        s.put("k" + std::to_string(i), i);

    s.begin();                       // outer
    for (int depth = 0; depth < 10; ++depth) {
        s.begin();                   // inner
        for (int i = 0; i < N; ++i)
            s.put("k" + std::to_string(i), (depth + 1) * 1000 + i);
        s.commit();                  // merge into parent
    }
    // All keys are now at 10000 + i
    for (int i = 0; i < N; ++i)
        EXPECT_EQ(s.get("k" + std::to_string(i)).value(), 10000 + i);

    s.rollback();                    // outer — everything back to original
    for (int i = 0; i < N; ++i)
        EXPECT_EQ(s.get("k" + std::to_string(i)).value(), i);
}

TEST(stress_mixed_random_operations) {
    KVStore s;
    std::mt19937 rng(42);
    const int OPS = 15000;
    std::map<std::string, int> ref;

    {
        practice::ScopedTimer t(std::to_string(OPS) + " random put/get/remove");
        for (int i = 0; i < OPS; ++i) {
            std::string key = "k" + std::to_string(rng() % 800);
            int op = rng() % 3;
            if (op == 0) {
                int val = rng() % 10000;
                s.put(key, val);
                ref[key] = val;
            } else if (op == 1) {
                auto got = s.get(key);
                auto it = ref.find(key);
                if (it != ref.end()) {
                    EXPECT(got.has_value());
                    if (got.has_value())
                        EXPECT_EQ(got.value(), it->second);
                } else {
                    EXPECT(!got.has_value());
                }
            } else {
                s.remove(key);
                ref.erase(key);
            }
        }
    }
    EXPECT_EQ(s.count(), ref.size());
}

int main() {
    return practice::run_all_tests();
}
