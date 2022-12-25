
#pragma once

#include <iostream>
#include <string>

namespace toffee {

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
 public:
  Colorize(ColorTint color) : value_(static_cast<int>(color)) { }
  Colorize(FontStyle style) : value_(static_cast<int>(style)) { }
  Colorize(unsigned char code) : value_(static_cast<int>(code)) { }
  Colorize(std::string comple_code) : complete_code_(comple_code) { }

  static std::ostream &Reset(std::ostream &out);

  std::ostream& operator ()(std::ostream &out) const;
  friend std::ostream& operator <<(std::ostream &out, const Colorize& colorize);

 private:
  int value_;
  std::string complete_code_;

};

inline std::ostream& Reset(std::ostream& out) {
  return out << "\u001b[0m";
}

inline std::ostream& Colorize::operator ()(std::ostream& out) const {
  if (complete_code_.empty()) {
    return out << "\u001b[" << value_ << "m";
  }
  return out << "\u001b[" << complete_code_ << "m";
}

inline std::ostream& operator <<(std::ostream& out, const Colorize& colorize) {
  return colorize(out);
}

}
