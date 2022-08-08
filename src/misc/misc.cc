/**
 * @file utils.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <limits>
#include <iomanip>
#include <cmath>

#include "utils/misc.h"
#include "utils/colors.h"

namespace utils {

/**
 * @brief Returns if the input_number is natural
 * @param input_number 
 * @return true 
 * @return false 
 */
bool IsNatural(const int& input_number) {
  return input_number > 0;
}

/**
 * @brief Prints an stylized header with the specfied text
 * @param header_text 
 */
void PrintHeader(const std::string& header_text) {
  std::cout << std::setfill('*') << std::setw(100) << "*" << std::endl;
  std::cout << std::setfill(' ') << std::setw(20) << header_text << std::endl;
  std::cout << std::setfill('*') << std::setw(100) << "*" << std::endl;
}

void PrintAskPrompt(const std::string& prompt) {
  std::cout << utils::Colorize(utils::ColorTint::kGreen) << "? " << utils::Colorize::Reset;
  std::cout << utils::Colorize(utils::FontStyle::kBold) << prompt << ": " << utils::Colorize::Reset;
  return;
}

/**
 * @brief Returns the sum of the specified number of digits, 
 * starting from the last one
 * @param input_number 
 * @param number_of_digits 
 * @return int 
 */
int SumOfNLastDigits(const int& input_number, const int& number_of_digits) {
  int last_digits_sum = 0;
  int leftover_number = input_number;
  for (int current_digit = 0; current_digit < number_of_digits; ++current_digit) {
    last_digits_sum += leftover_number % 10;
    leftover_number /= 10;
  }
  return last_digits_sum;
}

/**
 * @brief Returns the number of digits of the input_number
 * @param input_number 
 * @return int 
 */
int CountDigits(const int& input_number) {
  return log10(input_number) + 1;
}

bool IsAlpha(const char input_char) {
  if (input_char >= 'a' && input_char <= 'z') {
    return true;
  } else if (input_char >= 'A' && input_char <= 'Z') {
    return true;
  }
  return false;
}

bool IsUppercase(const char input_char) {
  if (input_char >= 'A' && input_char <= 'Z') {
    return true;
  }
  return false;
}

}