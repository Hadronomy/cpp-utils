/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica 2021-2022
 *
 * @file counting_frequences.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * @see whatever
 */

#include <iostream>
#include <map>
#include <vector>

#ifndef _JUDGE_
#include "lib/utils.h"
#endif  //  !_JUDGE_

using input_size = long int;

/**
 * @brief Counts the repetitions of all the elements of the %input_sequence
 * 
 * @param input_sequence 
 * @return std::map<input_size, int> 
 */
std::map<input_size, int> CountRepetitions(const std::vector<input_size>& input_sequence) {
  std::map<input_size, int> repetition_map;
  for (int current_index = 0; current_index < input_sequence.size(); ++current_index) {
    repetition_map[input_sequence[current_index]] += 1;
  }
  return repetition_map;
}

/**
 * @brief Prints a map to the standard output stream
 * 
 * @param input_map 
 */
void PrintMap(const std::map<input_size, int>& input_map) {
  for (auto map_element : input_map) {
    std::cout << map_element.first << " : " << map_element.second << std::endl;
  }
  return;
}

int main() {
#ifndef _JUDGE_
  utils::PrintHeader("Este programa cuenta las repeticiones de los números de una secuencia");
  utils::PrintAskPrompt("Introduce el número de elementos que tendrá la secuencia");
#endif  //  _JUDGE_
  int input_amount;
  std::cin >> input_amount;
  std::vector<input_size> input_numbers;
#ifndef _JUDGE_
  utils::PrintAskPrompt("Introduce la secuencia");
#endif  //  !_JUDGE_
  input_numbers.resize(input_amount);
  for (int current_input = 0; current_input < input_amount; ++current_input) {
    std::cin >> input_numbers[current_input];
  }
#ifndef _JUDGE_
  std::cout << utils::Colorize(utils::ColorTint::kGreen) << utils::Colorize(utils::FontStyle::kBold);
  std::cout << "Resultado: " << utils::Colorize::Reset << std::endl;
#endif  //  !_JUDGE_
  PrintMap(CountRepetitions(input_numbers));
  return 0;
}