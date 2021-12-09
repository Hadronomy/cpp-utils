/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica 2021-2022
 *
 * @file balanced_number.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * @see https://jutge.org/problems/P26492_en
 */

#include <iostream>
#include <cmath>

#ifndef _JUDGE_
#include "lib/utils.h"
#endif  //  !_JUDGE_

/**
 * @brief Returns the digit of %input_number at $digit_position
 * 
 * @param input_number 
 * @param digit_position 
 * @return int 
 */
int GetDigitAt(const int input_number, const int digit_position) {
  int digits = log10(input_number) + 1;
  int inverse_pos = pow(10, abs(digit_position - digits) - 1);
  int digit = (int)floor(input_number / inverse_pos) % 10;
  return digit;
}

/**
 * @brief Returns true if the %input_number is balanced
 * 
 * @param input_number The number to check if it's balanced
 * @return true 
 * @return false 
 */
bool IsBalanced(const int input_number) {
  int digits = log10(input_number) + 1;
  int even_numbers = ceil(digits / 2.0);
  int odd_numbers = digits - even_numbers;
  int even_sum = 0;
  int odd_sum = 0;
  for (int current_even = 0; current_even < even_numbers; ++current_even) {
    even_sum += GetDigitAt(input_number, current_even * 2);
  }
  for (int current_odd = 0; current_odd < odd_numbers; ++current_odd) {
    odd_sum += GetDigitAt(input_number, current_odd * 2 + 1);
  }
  return even_sum == odd_sum;
}

/**
 * @brief Wrapper for the %IsBalanced(const int input_number) to be used in Jutge
 * 
 * @param n 
 * @return true 
 * @return false 
 */
bool is_balanced(int n) {
  return IsBalanced(n);
}

int main() {
#ifndef _JUDGE_
  utils::PrintHeader("Este programa comprueba si el número introducido está equilibrado");
  utils::PrintAskPrompt("Introduce un número");
#endif  //  !_JUDGE_
  int input_number;
  while (std::cin >> input_number) {
#ifndef _JUDGE_
  std::cout << utils::Colorize(utils::ColorTint::kGreen) << utils::Colorize(utils::FontStyle::kBold);
  std::cout << "Resultado: " << utils::Colorize::Reset;
#endif  //  !_JUDGE_
    std::cout << IsBalanced(input_number) << std::endl;
  }
  return 0;
}