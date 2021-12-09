/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica 2021-2022
 *
 * @file caesar_cipher.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * @see https://jutge.org/problems/P33371_en
 */

#include <iostream>
#include <string>
#include <sstream>

#ifndef _JUDGE_
#include "lib/utils.h"
#endif  //  !_JUDGE_

/**
 * @brief Encodes the %input_char using Caesar Cypher algorithm and %key as key
 * Note: The resulting char will be in uppercase
 * @param input_char 
 * @param key 
 * @return char 
 */
char CaesarEncode(const char input_char, const int key) {
  const int kStartingLowercase = 'a';
  const int kEndingLowercase = 'z';
  const int kAlphabeticalLenght = 'z' - 'a' + 1;
  if (input_char < kStartingLowercase || input_char > kEndingLowercase) {
    return input_char;
  }
  int displaced_char = input_char + key;
  displaced_char = ((displaced_char - kStartingLowercase) %  kAlphabeticalLenght) + 'A';
  return displaced_char;
}

/**
 * @brief Wrapper function of %CaesarEncode(const char input_char, const int key)
 * 
 * @param c 
 * @param k 
 * @return char 
 */
char encoded(char c, int k) {
  return CaesarEncode(c, k);
}

int main() {
#ifndef _JUDGE_
  utils::PrintHeader("Este programa cifra con Caesar Cipher un texto introducido usando una key introducida");
  utils::PrintAskPrompt("Introduce el valor del desplazamiento (key)");
#endif
  int encoding_key;
  std::string input_string;
  while (std::cin >> encoding_key) {
    std::cin.ignore();
    std::getline(std::cin, input_string);
    std::stringstream encoded_string("");
    for (int current_index = 0; current_index < input_string.size(); ++current_index) {
      char current_char = input_string[current_index];
      if (current_char != '.') {
        if (current_char == '_') {
          current_char = ' ';
        }
        encoded_string << CaesarEncode(current_char, encoding_key);
      }
      
    }
    std::cout << encoded_string.str() << std::endl;
  }
  return 0;
}