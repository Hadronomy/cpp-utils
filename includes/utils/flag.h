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

#ifndef LIB_UTILS_CLI_OPT_
#define LIB_UTILS_CLI_OPT_

#include <vector>
#include <string>

namespace utils {

/**
 * @brief Defines the basic data structure of a cli option
 * 
 */
class Flag {
 public:
  Flag(std::string name, std::string alias, std::string description, bool is_overriding) : 
    name_(name), alias_(alias), description_(description), is_overriding_(is_overriding) { }
  Flag(std::string name, std::string alias, const char* description) : 
    name_(name), alias_(alias), description_(std::string(description)) { }
  Flag(std::string name, std::string description, bool is_overriding = false) :
    name_(name), description_(description), is_overriding_(is_overriding) { }

  std::string GetName() const {
    return name_;
  }

  std::string GetDescription() const {
    return description_;
  }

  std::string GetAlias() const {
    return alias_;
  }

  bool IsOverriding() const {
    return is_overriding_;
  }

 private:
  Flag();

  std::string name_;
  std::string alias_;
  std::string description_;
  bool is_overriding_;
};

} // namespace utils

#endif  //  !LIB_UTILS_CLI_OPT_