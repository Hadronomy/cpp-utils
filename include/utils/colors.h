/**
 * @file colors.h
 * @author Pablo Hernández Jiménez
 * @brief 
 * @version 1.0
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <iostream>
#include <string>

namespace utils {

/**
 * @brief Font colors identifiers for console logging
 * 
 */
enum class ColorTint {
  kReset = 0,
  kBlack = 30,
  kRed = 31,
  kGreen = 32,
  kYellow = 33,
  kBlue = 34,
  kMagenta = 35,
  kCyan = 36,
  kWhite = 37
};

/**
 * @brief Font styles identifiers for console logging
 * 
 */
enum class FontStyle {
  kBold = 1,
  kUnderline = 4,
  kReversed = 7
};

/**
 * @brief Utility class that manages the styling of the output stream
 * 
 */
class Colorize {
 private:
  int value_;
  std::string complete_code_;

 public:
  Colorize(ColorTint color) : value_(static_cast<int>(color)) { }

  Colorize(FontStyle style) : value_(static_cast<int>(style)) { }

  Colorize(unsigned char code) : value_(static_cast<int>(code)) { }

  Colorize(std::string comple_code) : complete_code_(comple_code) { }

 public:
  static std::ostream &Reset(std::ostream &out);

  /**
   * @brief Colorizes the output stream
   * @return std::ostream& 
   */
  std::ostream &operator()(std::ostream &out) const;

};

std::ostream &operator <<(std::ostream &out, Colorize colorize);

}