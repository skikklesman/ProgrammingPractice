#pragma once
#include <optional>
#include <string>
#include <utility>
#include <vector>

class KVStore {
public:
    void put(const std::string& key, int value);
    std::optional<int> get(const std::string& key) const;
    bool remove(const std::string& key);

    void begin();
    bool commit();
    bool rollback();

    std::vector<std::pair<std::string, int>> range_query(
        const std::string& lo, const std::string& hi) const;

    size_t count() const;
    bool in_transaction() const;

private:
    // Flat storage — every operation is a linear scan.
    std::vector<std::pair<std::string, int>> store_;

    // Transaction undo stack: each active transaction keeps a log of
    // (key, previous-value-or-nullopt) entries so rollback can restore state.
    std::vector<std::vector<std::pair<std::string, std::optional<int>>>> undo_stack_;

    int find_key(const std::string& key) const;
};
