#pragma once
// Minimal test harness — no external dependencies.
//
// Usage:
//   TEST(name) { EXPECT(expr); EXPECT_EQ(a, b); }
//   // in main(): return run_all_tests();

#include <cmath>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace practice {

template <class T>
struct is_std_vector : std::false_type {};
template <class T, class A>
struct is_std_vector<std::vector<T, A>> : std::true_type {};

template <class T>
void write_value(std::ostream& os, const T& v) {
    if constexpr (is_std_vector<T>::value) {
        os << "[";
        for (std::size_t i = 0; i < v.size(); ++i) {
            if (i) os << ", ";
            write_value(os, v[i]);
        }
        os << "]";
    } else {
        os << v;
    }
}


struct TestCase {
    std::string name;
    std::function<void()> body;
};

inline std::vector<TestCase>& test_registry() {
    static std::vector<TestCase> tests;
    return tests;
}

inline int& failure_count() {
    static int n = 0;
    return n;
}

struct TestRegistrar {
    TestRegistrar(const char* name, std::function<void()> body) {
        test_registry().push_back({name, std::move(body)});
    }
};

inline void report_failure(const char* file, int line, const std::string& msg) {
    std::cerr << "  FAIL  " << file << ":" << line << " — " << msg << "\n";
    ++failure_count();
}

inline int run_all_tests() {
    int passed = 0, failed = 0;
    for (auto& tc : test_registry()) {
        int before = failure_count();
        std::cout << "[ RUN  ] " << tc.name << "\n";
        try {
            tc.body();
        } catch (const std::exception& e) {
            report_failure(__FILE__, __LINE__, std::string("exception: ") + e.what());
        }
        if (failure_count() == before) {
            std::cout << "[ PASS ] " << tc.name << "\n";
            ++passed;
        } else {
            std::cout << "[ FAIL ] " << tc.name << "\n";
            ++failed;
        }
    }
    std::cout << "\n" << passed << " passed, " << failed << " failed.\n";
    return failed == 0 ? 0 : 1;
}

}  // namespace practice

#define TEST(name)                                                              \
    static void test_##name();                                                  \
    static ::practice::TestRegistrar reg_##name(#name, test_##name);            \
    static void test_##name()

#define EXPECT(expr)                                                            \
    do {                                                                        \
        if (!(expr))                                                            \
            ::practice::report_failure(__FILE__, __LINE__, #expr);              \
    } while (0)

#define EXPECT_EQ(a, b)                                                         \
    do {                                                                        \
        auto&& _a = (a);                                                        \
        auto&& _b = (b);                                                        \
        if (_a != _b) {                                                         \
            std::ostringstream _os;                                             \
            _os << #a " == " #b " (";                                           \
            ::practice::write_value(_os, _a);                                   \
            _os << " vs ";                                                      \
            ::practice::write_value(_os, _b);                                   \
            _os << ")";                                                         \
            ::practice::report_failure(__FILE__, __LINE__, _os.str());          \
        }                                                                       \
    } while (0)

#define EXPECT_NEAR(a, b, tol)                                                  \
    do {                                                                        \
        auto&& _a = (a);                                                        \
        auto&& _b = (b);                                                        \
        if (std::fabs(_a - _b) > (tol)) {                                      \
            std::ostringstream _os;                                             \
            _os << #a " ≈ " #b " (" << _a << " vs " << _b                    \
                << ", tol=" << (tol) << ")";                                    \
            ::practice::report_failure(__FILE__, __LINE__, _os.str());          \
        }                                                                       \
    } while (0)
