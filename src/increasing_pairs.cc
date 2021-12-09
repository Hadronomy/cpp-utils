/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica 2021-2022
 *
 * @file increasing_pairs.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * @see https://jutge.org/problems/P73501_en
 */

#include <iostream>
#include <vector>

#ifndef _JUDGE_
#include "lib/utils.h"
#endif  //  !_JUDGE_

int main() {
#ifndef _JUDGE_
  utils::PrintHeader("Este programa calcula el número de parejas consecutivas cuyo segundo valor es mayor al primero");
  utils::PrintAskPrompt("Introduce el número de secuencias");
#endif  //  !_JUDGE_
  int sequence_amount;
  std::cin >> sequence_amount;
  for (int current_sequence = 0; current_sequence < sequence_amount; current_sequence++) {
#ifndef _JUDGE_
  utils::PrintAskPrompt("Introduce la secuencia de parejas ('0' finaliza la secuencia)");
#endif  //  !_JUDGE_
    int consecutives_count = 0;
    int first_element;
    int second_element;
    std::cin >> first_element;
    while (first_element > 0) {
      std::cin >> second_element;
      if (first_element < second_element) {
        ++consecutives_count;
      }
      first_element = second_element;
    }
#ifndef _JUDGE_
    std::cout << utils::Colorize(utils::ColorTint::kGreen) << utils::Colorize(utils::FontStyle::kBold);
    std::cout << "Resultado: " << utils::Colorize::Reset;
#endif  //  !_JUDGE_
    std::cout << consecutives_count << std::endl;
  }
  return 0;
}