/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica 2021-2022
 * 
 * @file equal_last.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * @see https://jutge.org/problems/P14130_en/submissions/S003
 */

#include <iostream>
#include <algorithm>
#include <vector>

#ifndef _JUDGE_
#include "lib/utils.h"
#endif  //  !_JUDGE_

/**
 * @brief Searchs and counts the %querry_number in %sequence
 * @param sequence 
 * @param querry_number 
 * @return int 
 */
int CountNumberInSequence(const std::vector<int>& sequence, const int querry_number) {
  return std::count(sequence.begin(), sequence.end(), querry_number);
}

int main() {
#ifndef _JUDGE_
  utils::PrintHeader("Este programa pide que introduzcas una sequencia de tamaño especificado por el usuario y devuelve el número de repeticiones del último valor");
  utils::PrintAskPrompt("Introduce el número de elementos de la sequencia");
#endif
  int input_amount;
  std::cin >> input_amount;
  std::vector<int> sequence;
  for (int current_input = 0; current_input < input_amount - 1; ++current_input) {
    int current_number;
    std::cin >> current_number;
    sequence.push_back(current_number);
  }
  int querry_number;
  std::cin >> querry_number;
#ifndef _JUDGE_
  std::cout << utils::Colorize(utils::ColorTint::kGreen) << utils::Colorize(utils::FontStyle::kBold);
  std::cout << "Resultado: " << utils::Colorize::Reset;
#endif
  std::cout << CountNumberInSequence(sequence, querry_number) << std::endl;
  return 0;
}