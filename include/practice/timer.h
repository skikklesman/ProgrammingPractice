#pragma once
// Simple RAII timer for performance exercises.
//
// Usage:
//   {
//       practice::ScopedTimer t("my_operation");
//       // ... code to measure ...
//   }  // prints elapsed time on destruction

#include <chrono>
#include <iostream>
#include <string>

namespace practice {

class ScopedTimer {
public:
    explicit ScopedTimer(std::string label)
        : label_(std::move(label)),
          start_(std::chrono::high_resolution_clock::now()) {}

    ~ScopedTimer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start_).count();
        if (us < 1000)
            std::cout << "[TIMER] " << label_ << ": " << us << " µs\n";
        else
            std::cout << "[TIMER] " << label_ << ": " << us / 1000.0 << " ms\n";
    }

    ScopedTimer(const ScopedTimer&) = delete;
    ScopedTimer& operator=(const ScopedTimer&) = delete;

private:
    std::string label_;
    std::chrono::high_resolution_clock::time_point start_;
};

}  // namespace practice
