/**
 * @file utils.h
 * @author Pablo Hernández Jiménez
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

namespace utils {

struct DefaultType {
 public:
  template<typename T>
  operator T() const { return T(); }
};

const DefaultType kDefault = DefaultType();

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
 * (Doesn't interact with cin)s
 * @param prompt 
 */
void PrintAskPrompt(const std::string& prompt);

/**
 * @brief Waits for the user to press enter
 * NOTE: It doesn't print anything
 */
void WaitForEnter();

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

/**
 * @brief Returns true if the input char is alpha
 * 
 * @param input_char 
 * @return true 
 * @return false 
 */
bool IsAlpha(const char input_char);

/**
 * @brief Returns true if the input char is an alpha
 * uppercase char
 * 
 * @param input_char 
 * @return true 
 * @return false 
 */
bool IsUppercase(const char input_char);

/**
 * @brief
 * Repeats the process of shifting and copying the
 * given bits an specified amount of times
 * @tparam TInt
 * @param initial The bits to shift and copy
 * @param amount The amount of times to shift and copy
 * @example
 * ShiftCopyBit<uint8_t>(1, 4) => 0x00001111;
 * @return
 */
template<class TInt>
constexpr TInt ShiftCopyBit(TInt initial, size_t amount) {
  for (int i = 0; i < amount; initial |= initial << i, ++i);
  return initial;
}

}  // namespace utils
