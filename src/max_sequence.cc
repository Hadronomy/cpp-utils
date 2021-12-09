/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica 2021-2022
 *
 * @file max_sequence.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * @see https://jutge.org/problems/P71753_en
 */

#include <iostream>
#include <algorithm>
#include <vector>

#ifndef _JUDGE_
#include "lib/utils.h"
#endif  //  !_JUDGE_

/**
 * @brief Returns the max element of %sequence
 * 
 * @param sequence 
 * @return int 
 */
int MaxElement(const std::vector<int>& sequence) {
  return *std::max_element(sequence.begin(), sequence.end());
}

int main() {
#ifndef _JUDGE_
  utils::PrintHeader("Este programa busca el máximo elemento de una sequencia introducida");
  utils::PrintAskPrompt("Introduce el número de elementos de la sequencia");
#endif
  int input_amount;
  while (std::cin >> input_amount) {
    std::vector<int> input_sequence;
    input_sequence.resize(input_amount);
#ifndef _JUDGE_
    utils::PrintAskPrompt("Introduce la sequencia");
#endif
    for (int current_input = 0; current_input < input_amount; ++current_input) {
      std::cin >> input_sequence[current_input];
    }
#ifndef _JUDGE_
    std::cout << utils::Colorize(utils::ColorTint::kGreen) << utils::Colorize(utils::FontStyle::kBold);
    std::cout << "Resultado: " << utils::Colorize::Reset;
#endif
    std::cout << MaxElement(input_sequence) << std::endl;
  }
  return 0;
}