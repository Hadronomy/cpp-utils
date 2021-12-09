/**
 * @file utils.h
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief Defines a series of utility functions that are repeatedly used in
 * this project
 * @version 1.0
 * @date 2021-11-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <limits>
#include <string>
#include <map>
#include <vector>

#include "utils/hourglass.h"
#include "utils/colors.h"
#include "utils/cli.h"

#ifndef LIB_UTILS_H
#define LIB_UTILS_H

namespace utils {

/**
* @brief Returns true if the passed values overflows it's allowed size
* @tparam TNumeric
* @param value_to_check
* @return True if there's an overflow
*/
template<
  typename TNumeric,
  typename = typename std::enable_if<std::is_arithmetic<TNumeric>::value, TNumeric>::type
>
bool HasOverflow(const TNumeric& value_to_check) {
  return value_to_check >= std::numeric_limits<TNumeric>::max();
}

/**
 * @brief Prints a prettified prompt message
 * (Doesn't interact with cin)
 * @param prompt 
 */
void PrintAskPrompt(const std::string& prompt);

/**
 * @brief Returns if the input_number is natural
 * @param input_number 
 * @return true 
 * @return false 
 */
bool IsNatural(const int& input_number);

/**
 * @brief Prints an stylized header with the specfied text
 * @param header_text 
 */
void PrintHeader(const std::string& header_text);

/**
 * @brief Returns the sum of the specified number of digits, 
 * starting from the last one
 * @param input_number 
 * @param number_of_digits 
 * @return int 
 */
int SumOfNLastDigits(const int& input_number, const int& number_of_digits);

/**
 * @brief Returns the number of digits of the input_number
 * @param input_number 
 * @return int 
 */
int CountDigits(const int& input_number);

}  // namespace utils

#endif //  LIB_UTILS_H
