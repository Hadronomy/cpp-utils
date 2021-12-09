/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica 2021-2022
 *
 * @file maximum_sums.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * @see https://jutge.org/problems/P20262_en
 */

#include <iostream>
#include <vector>

#ifndef _JUDGE_
#include "lib/utils"
#endif  //  !_JUDGE_

/**
 * @brief Operates the sum of all the number in the sequence from right to left
 * and from left to right. Returns the maximum sum posible from each direction.
 * 
 * @param sequence 
 * @return std::pair<int, int> 
 */
std::pair<int, int> MaximumSums(const std::vector<int>& sequence) {
  int max_left_right = 0;
  int sum_left_right = 0;
  for (int current_index = 0; current_index < sequence.size(); ++current_index) {
    sum_left_right += sequence[current_index];
    if (sum_left_right > max_left_right) {
      max_left_right = sum_left_right;
    }
  }
  int max_right_left = 0;
  int sum_right_left = 0;
  for (int current_index = sequence.size() - 1; current_index >= 0; --current_index) {
    sum_right_left += sequence[current_index];
    if (sum_right_left > max_right_left) {
      max_right_left = sum_right_left;
    }
  }
  return std::make_pair(max_right_left, max_left_right);
}

int main() {
#ifndef _JUDGE_
  utils::PrintHeader("Este programa opera la suma de la secuencia de izquierda a derecha y vis e versa, \n devolviendo el valor máximo.");
  utils::PrintAskPrompt("Introduce el número de secuencias");
#endif  //  !_JUDGE_
  int input_amount = 0;
  while(std::cin >> input_amount) {
    std::vector<int> input_numbers;
    input_numbers.resize(input_amount);
    for (int current_input = 0; current_input < input_amount; ++current_input) {
      std::cin >> input_numbers[current_input];
    }
    auto maximum_sums = MaximumSums(input_numbers);
    std::cout << maximum_sums.second << " " << maximum_sums.first << std::endl;
  }
  return 0;
}