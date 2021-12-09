/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica 2021-2022
 *
 * @file mersenne.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * @see 
 */

#include <iostream>
#include <vector>
#include <cmath>

#include "lib/utils.h"
#include "lib/mersenne/functions.h"

int main(int arg_count, char *arg_vector[]) {
  utils::Cli cli(
    "mersenne", 
    {utils::Argument("amount", "The amount of mersenne primes to generate")}, 
    {utils::Flag("help", "h", "Prints the command info"),}
  );
  cli.Parse(arg_count, arg_vector);
  if (cli.GetOption("help")) {
    cli.ShowHelp();
    return 0;
  }
  int primes_amount;
  primes_amount = stoi(cli.GetArgument("amount"));
  std::vector<int> primes = GenerateNPrimes(primes_amount);
  std::cout << utils::Colorize(utils::ColorTint::kGreen) << utils::Colorize(utils::FontStyle::kBold);
  std::cout << "Results: " << utils::Colorize::Reset << std::endl;
  for (int prime : primes) {
    std::cout << MersennePrime(prime) << std::endl;
  }
  return 0;
}