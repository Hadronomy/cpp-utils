/**
 * @file cli.h
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#ifndef LIB_UTILS_CLI_
#define LIB_UTILS_CLI_

#include <vector>
#include <string>
#include <map>

#include "argument.h"
#include "option.h"

namespace utils {

/**
 * @brief Utility class to manage cli argument parsing
 * 
 */
class Cli {
 public:
  Cli(std::string name, std::vector<Argument> arguments, std::vector<Option> options) {
    name_ = name;
    arguments_ = arguments;
    options_ = options;
  }

  /**
   * @brief Parses the execution arguments based on the cli expected arguments and
   * expected options
   * 
   * @param argument_count The amount of passed arguments
   * @param arguments The list of passed arguments
   */
  void Parse(const int &argument_count, char* arguments[]);

  /**
   * @brief Prints this cli help to the standard output
   * 
   */
  void ShowHelp();

  /**
   * @brief Gets the value passed as an argument of name %name
   * 
   * @param name The name of the argument to look for
   * @return std::string The argument value
   */
  std::string GetArgument(const std::string& name);

  /**
   * @brief Returns true if the option with name %name
   * was defined
   * 
   * @param name The name of the option to search
   * @return true 
   * @return false 
   */
  bool GetOption(const std::string& name);

 private:
  std::vector<std::string> tokens_;

  std::string name_;
  std::vector<Argument> arguments_;
  std::vector<Option> options_;

  std::map<std::string, std::string> parsed_arguments_;
  std::vector<std::string> parsed_options_;
};

}


#endif  //  LIB_UTILS_CLI_