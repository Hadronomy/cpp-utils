/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica 2021-2022
 *
 * @file statistical_measures.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * @see https://jutge.org/problems/P17179_en
 */

#include <iostream>
#include <iomanip>
#include <tuple>
#include <vector>

#ifndef _JUDGE_
#include "lib/utils.h"
#endif  //  !_JUDGE_

/**
 * @brief Returns the Min, Max and Mean of a sequence
 * 
 * @param input_sequence The sequence from where to operate the min, max and average
 * @return std::tuple<double, double, double> 
 */
std::tuple<double, double, double> MinMaxMean(const std::vector<double>& input_sequence) {
  double max = input_sequence[0];
  double min = input_sequence[0];
  double sum = 0;
  for (int current_input = 0; current_input < input_sequence.size(); ++current_input) {
    double current_element = input_sequence[current_input];
    if (current_element > max) {
      max = current_element;
    }
    if (current_element < min) {
      min = current_element;
    }
    sum += current_element;
  }
  double mean = sum / static_cast<double>(input_sequence.size());
  return std::make_tuple(min, max, mean);
}

int main() {
#ifndef _JUDGE_
  utils::PrintHeader("Este programa calcula el mínimo, máximo y la media de 'n' secuencias introducidas");
  utils::PrintAskPrompt("Introduce el número de secuencias");
#endif  //  !_JUDGE_
  std::cout << std::fixed;
  std::cout << std::setprecision(4);
  int sequence_amount;
  std::cin >> sequence_amount;
  for (int current_sequence = 0; current_sequence < sequence_amount; ++current_sequence) {
#ifndef _JUDGE_
    utils::PrintAskPrompt("Introduce el tamaño de la secuencia");
#endif  //  !_JUDGE_
    int input_amount;
    std::cin >> input_amount;
    std::vector<double> input_sequence;
    input_sequence.resize(input_amount);
#ifndef _JUDGE_
      utils::PrintAskPrompt("Introduce la secuencia");
#endif  //  !_JUDGE_
    for (int current_input = 0; current_input < input_amount; ++current_input) {
      std::cin >> input_sequence[current_input];
    }
    auto min_max_mean = MinMaxMean(input_sequence);
#ifndef _JUDGE_
    std::cout << utils::Colorize(utils::ColorTint::kGreen) << utils::Colorize(utils::FontStyle::kBold);
    std::cout << "Resultado: " << utils::Colorize::Reset;
#endif  //  !_JUDGE_
    std::cout << std::get<0>(min_max_mean) << " " << std::get<1>(min_max_mean) << " " << std::get<2>(min_max_mean) << std::endl;
  }
  return 0;
}