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
  Flag(std::string name, std::string alias, std::string description) {
    name_ = name;
    description_ = description;
    alias_ = alias;
  }

  std::string GetName() {
    return name_;
  }

  std::string GetDescription() {
    return description_;
  }

  std::string GetAlias() {
    return alias_;
  }
 private:
  std::string name_;
  std::string description_;
  std::string alias_;

};

} // namespace utils

#endif  //  !LIB_UTILS_CLI_OPT_