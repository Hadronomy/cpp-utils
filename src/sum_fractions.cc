/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica 2021-2022
 *
 * @file sum_fractions.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * @see https://jutge.org/problems/P76024_en
 */

#include <iostream>
#include <iomanip>

#ifndef _JUDGE_
#include "lib/utils.h"
#endif  //  !_JUDGE_

/**
 * @brief Sums all fractions => 1 / %constant_denominator + i * %variable_denominator, where the resulting denominator
 * is lower or equal than max_denominator
 * 
 * @param constant_denominator 
 * @param variable_denominator 
 * @param max_denominator 
 * @return double 
 */
double FractionsSum(const int constant_denominator, const int variable_denominator, const int max_denominator) {
  double fractions_sum = 0.0;
  int current_denominator = constant_denominator;
  for (int current_denominator_multiplier = 1; current_denominator <= max_denominator; ++current_denominator_multiplier) {
    fractions_sum += 1.0 / static_cast<double>(current_denominator);
    current_denominator = constant_denominator + current_denominator_multiplier * variable_denominator;
  }
  return fractions_sum;
}

int main() {
#ifndef _JUDGE_
  utils::PrintHeader("Este programa realiza lo solicitado en https://jutge.org/problems/P76024_en");
  utils::PrintAskPrompt("Introduce el denominador constante, variable y máximo");
#endif  //  !_JUDGE_
  int constant_denominator, variable_denominator, max_denominator;
  while (std::cin >> constant_denominator >> max_denominator >> variable_denominator) {
#ifndef _JUDGE_
    std::cout << utils::Colorize(utils::ColorTint::kGreen) << utils::Colorize(utils::FontStyle::kBold);
    std::cout << "Resultado: " << utils::Colorize::Reset;
#endif  //  !_JUDGE_
    std::cout << std::setprecision(4) << std::fixed;
    std::cout << FractionsSum(constant_denominator, variable_denominator, max_denominator) << std::endl;
  }
  return 0;
}