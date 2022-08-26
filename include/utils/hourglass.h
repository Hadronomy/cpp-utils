/**
 * @file hourglass.h
 * @author Pablo Hernández Jiménez
 * @brief 
 * @version 1.0
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <chrono>
#include <stack>
#include <iostream>

namespace utils {

/**
 * @brief A utility class for managing time
 * 
 */
class Hourglass {
 public:
  static void Start();
  static Hourglass Stop();
  [[nodiscard]] double Elapsed() const;

  friend std::ostream& operator<<(std::ostream& out, const Hourglass& hourglass);
 private:
  Hourglass() : start_(clock_t::now()) { }
  static std::stack<Hourglass> timers_;

  using clock_t = std::chrono::high_resolution_clock;
  using milli_t = std::chrono::duration<double, std::milli>;

  std::chrono::time_point<clock_t> start_;
  std::chrono::time_point<clock_t> end_;
};

}
