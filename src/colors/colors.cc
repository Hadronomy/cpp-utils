/**
 * @file colors.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>

#include "utils/colors.h"

namespace utils {

std::ostream &Colorize::Reset(std::ostream &out) {
  return out << "\u001b[0m";
}

std::ostream &Colorize::operator()(std::ostream &out) const {
  if (complete_code_.empty()) {
    return out << "\u001b[" << value_ << "m";
  } else {
    return out << "\u001b[" << complete_code_ << "m";
  }
}

std::ostream &operator <<(std::ostream &out, Colorize colorize) {
  return colorize(out);
}

}