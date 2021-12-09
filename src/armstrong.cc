/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica 2021-2022
 *
 * @file parmstrong.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * @see
 */

#include <iostream>

#include "lib/utils.h"
#include "lib/armstrong/functions.h"

int main(int arg_count, char *arg_vector[]) {
  utils::Cli cli(
    "armstrong",
    {utils::Argument("test_number", "The number to test if is Armstrong or not")},
    {utils::Flag("help", "Prints the command info", "h")}
  );
  cli.Parse(arg_count, arg_vector);
  if (cli.GetOption("help")) {
    cli.ShowHelp();
    return 0;
  }
  int test_number;
  test_number = stoi(cli.GetArgument("test_number"));
  std::cout << utils::Colorize(utils::ColorTint::kGreen) << utils::Colorize(utils::FontStyle::kBold);
  std::cout << "Result: " << utils::Colorize::Reset;
  std::cout << utils::Colorize(utils::FontStyle::kBold) << test_number << utils::Colorize::Reset;
  if (IsArmstrong(test_number)) {
    std::cout << " is an Armstrong number" << std::endl;
  } else {
    std::cout << " is not an Armstrong number" << std::endl;
  }
  return 0;
}