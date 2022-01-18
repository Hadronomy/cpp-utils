/**
 * @file hourglass.h
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#ifndef LIB_UTILS_HOURGLASS_
#define LIB_UTILS_HOURGLASS_

#include <chrono>
#include <stack>

namespace utils {

/**
 * @brief A utility class for managing time
 * 
 */
class Hourglass {
 public:
  static void Start();
  static Hourglass Stop();
  double Elapsed() const;
 private:
  Hourglass() : start_(clock_t::now()) { }
  static std::stack<Hourglass> timers_;

  using clock_t = std::chrono::high_resolution_clock;
  using second_t = std::chrono::duration<double, std::ratio<1>>;

  std::chrono::time_point<clock_t> start_;
  std::chrono::time_point<clock_t> end_;
};

}

#endif  //  LIB_UTILS_HOURGLASS_
