/**
 * @file hourglass.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <chrono>
#include <stack>

#include "hourglass.h"

namespace utils {

std::stack<Hourglass> Hourglass::timers_;

void Hourglass::Start() {
  timers_.push(Hourglass());
}

Hourglass::Hourglass() {
  start_ = clock_t::now();
}

Hourglass Hourglass::Stop() {
  Hourglass ending_timer = timers_.top();
  ending_timer.end_ = clock_t::now();
  timers_.pop();
  return ending_timer;
}

double Hourglass::Elapsed() const {
  return std::chrono::duration_cast<second_t>(end_ - start_).count();
}

}