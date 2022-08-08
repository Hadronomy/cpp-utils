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

#include "utils/hourglass.h"
#include "utils/colors.h"

namespace utils {

std::stack<Hourglass> Hourglass::timers_;

/**
 * @brief Registers a new hourglass
 * 
 */
void Hourglass::Start() {
  timers_.push(Hourglass());
}

/**
   * @brief Stops the most recently started hourglass and returns it 
   * @return Hourglass 
   */
Hourglass Hourglass::Stop() {
  Hourglass ending_timer = timers_.top();
  ending_timer.end_ = clock_t::now();
  timers_.pop();
  return ending_timer;
}


/**
 * @brief Returns the elapsed from starting the hourglass and ending it
 * @return double 
 */
double Hourglass::Elapsed() const {
  return std::chrono::duration_cast<second_t>(end_ - start_).count();
}

/**
 * @brief Insertion operator for the hourglass class
 * 
 * @param out 
 * @param hourglass 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& out, const Hourglass& hourglass) {
  out << "Elapsed " << Colorize(FontStyle::kBold) << hourglass.Elapsed() << " ms";
  return out;
}

}