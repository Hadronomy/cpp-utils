/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica 2021-2022
 *
 * @file sequential_search.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * @see https://jutge.org/problems/P11725_en
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#ifndef _JUDGE_
#include "lib/utils.h"
#endif   //  !_JUDGE_

/**
 * @brief Searchs in %search_list the %querry_number, returns true if found
 * 
 * @param querry_number The number to search for existance
 * @param search_list The list where to search
 * @return true 
 * @return false 
 */
bool Exists(const int querry_number, const std::vector<int>& search_list) {
  for (int current_index = 0; current_index < search_list.size(); ++current_index) {
    if (search_list[current_index] == querry_number) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Wrapps the %Exists function
 * 
 * @param x 
 * @param V 
 * @return true 
 * @return false 
 */
bool exists(int x, const std::vector<int>& V) {
  return Exists(x, V);
}

#ifndef _JUDGE_
int main() {
  utils::PrintAskPrompt("Introduce el número a comprobar");
  int querry_number;
  std::cin >> querry_number;
  utils::PrintAskPrompt("Introduce la cantidad de elementos de la sequencia");
  int input_amount;
  std::cin >> input_amount;
  utils::PrintAskPrompt("Introduce la sequencia");
  std::vector<int> input_numbers;
  input_numbers.resize(input_amount);
  for (int current_input = 0; current_input < input_amount; ++current_input) {
    std::cin >> input_numbers[current_input];
  }
  std::cout << utils::Colorize(utils::ColorTint::kGreen) << utils::Colorize(utils::FontStyle::kBold);
  std::cout << "Resultado: " << utils::Colorize::Reset;
  utils::Hourglass::Start();
  std::cout << std::boolalpha << Exists(querry_number, input_numbers) << std::endl;
  double time_elapsed = utils::Hourglass::Stop().Elapsed();
  std::cout << utils::Colorize(utils::ColorTint::kCyan) << utils::Colorize(utils::FontStyle::kUnderline);
  std::cout << "Tardó: " << std::fixed << time_elapsed << utils::Colorize::Reset << std::endl;
  return 0;
}
#endif  //  _JUDGE_