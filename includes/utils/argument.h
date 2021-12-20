/**
 * @file argument.h
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#ifndef LIB_UTILS_CLI_ARG_
#define LIB_UTILS_CLI_ARG_

#include <vector>
#include <string>

#include <token.h>

namespace utils {

/**
 * @brief Defines the basic data structure of a cli argument
 * 
 */
class Argument : public Token {
 public:
  Argument(std::string name, std::string description) : 
    name_(name), description_(description) { }

  /**
   * @brief Get the Name
   * 
   * @return std::string 
   */
  std::string GetName() const {
    return name_;
  }

  /**
   * @brief Get the Description
   * 
   * @return std::string 
   */
  std::string GetDescription() const {
    return description_;
  }
  
 private:
  Argument();

  std::string name_;
  std::string description_;
};

} //  namespace utils

#endif  //  !LIB_UTILS_CLI_ARG_