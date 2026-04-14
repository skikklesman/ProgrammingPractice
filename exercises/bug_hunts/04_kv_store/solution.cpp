#include "solution.h"
#include <algorithm>

int KVStore::find_key(const std::string& key) const {
    for (int i = 0; i < static_cast<int>(store_.size()); ++i)
        if (store_[i].first == key) return i;
    return -1;
}

void KVStore::put(const std::string& key, int value) {
    if (!undo_stack_.empty()) {
        // Record previous value so rollback can restore it.
        auto prev = get(key);
        undo_stack_.back().push_back({key, prev});
    }

    int idx = find_key(key);
    if (idx >= 0)
        store_[idx].second = value;
    else
        store_.push_back({key, value});
}

std::optional<int> KVStore::get(const std::string& key) const {
    int idx = find_key(key);
    if (idx >= 0) return store_[idx].second;
    return std::nullopt;
}

bool KVStore::remove(const std::string& key) {
    int idx = find_key(key);
    if (idx < 0) return false;

    store_.erase(store_.begin() + idx);
    return true;
}

void KVStore::begin() {
    undo_stack_.push_back({});
}

bool KVStore::commit() {
    if (undo_stack_.empty()) return false;

    undo_stack_.pop_back();
    return true;
}

bool KVStore::rollback() {
    if (undo_stack_.empty()) return false;

    auto& log = undo_stack_.back();
    // Replay in reverse so the earliest change is restored last.
    for (int i = static_cast<int>(log.size()) - 1; i >= 0; --i) {
        auto& [key, prev] = log[i];
        if (prev.has_value()) {
            // Key existed before — restore its value.
            int idx = find_key(key);
            if (idx >= 0)
                store_[idx].second = prev.value();
            else
                store_.push_back({key, prev.value()});
        } else {
            // Key didn't exist before — remove it.
            int idx = find_key(key);
            if (idx >= 0)
                store_.erase(store_.begin() + idx);
        }
    }
    undo_stack_.pop_back();
    return true;
}

std::vector<std::pair<std::string, int>> KVStore::range_query(
    const std::string& lo, const std::string& hi) const {

    std::vector<std::pair<std::string, int>> result;
    for (auto& [k, v] : store_) {
        if (k >= lo && k < hi)
            result.push_back({k, v});
    }
    std::sort(result.begin(), result.end());
    return result;
}

size_t KVStore::count() const {
    return store_.size();
}

bool KVStore::in_transaction() const {
    return !undo_stack_.empty();
}
