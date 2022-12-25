
#pragma once

#include <chrono>
#include <stack>
#include <iostream>
#include <optional>

#include "colors.h"

namespace toffee {

/**
 * @brief A utility class for managing time
 * 
 */
class Hourglass {
 public:
  static void Start();
  static Hourglass Stop();
  double Elapsed() const;

  friend std::ostream& operator <<(std::ostream& out, const Hourglass& hourglass);
 private:
  Hourglass() : start_(clock_t::now()) { }

  static std::stack<Hourglass>& GetTimers();

  static std::optional<std::stack<Hourglass>> timers_;

  using clock_t = std::chrono::high_resolution_clock;
  using milli_t = std::chrono::duration<double, std::milli>;

  std::chrono::time_point<clock_t> start_;
  std::chrono::time_point<clock_t> end_;
};

std::optional<std::stack<Hourglass>> Hourglass::timers_;

std::stack<Hourglass>& Hourglass::GetTimers() {
  if (!timers_.has_value())
    timers_ = std::stack<Hourglass>();
  return timers_.value();
}

inline void Hourglass::Start() {
  GetTimers().push(Hourglass());
}

inline Hourglass Hourglass::Stop() {
  Hourglass ending_timer = GetTimers().top();
  ending_timer.end_ = clock_t::now();
  GetTimers().pop();
  return ending_timer;
}

inline double Hourglass::Elapsed() const {
  return std::chrono::duration_cast<milli_t>(end_ - start_).count();
}

inline std::ostream& operator <<(std::ostream& out, const Hourglass& hourglass) {
  out << "Elapsed " << Colorize(FontStyle::kBold) << hourglass.Elapsed() << " ms";
  return out;
}

}
