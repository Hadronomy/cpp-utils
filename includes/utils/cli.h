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
#include "flag.h"

namespace utils {

/**
 * @brief Utility class to manage cli argument parsing
 * 
 */
class Cli {
 public:
  Cli(std::string name, std::vector<Argument> arguments, std::vector<Flag> flags) : 
    name_(name), arguments_(arguments), flags_(flags) { }
  Cli(std::string name, std::vector<Argument> arguments) : 
    name_(name), arguments_(arguments) { }

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
  void ShowHelp() const;

  /**
   * @brief Gets the value passed as an argument of name %name
   * 
   * @param name The name of the argument to look for
   * @return std::string The argument value
   */
  std::string GetArgument(const std::string& name) const;

  /**
   * @brief Returns true if the flag with name %name
   * was defined
   * 
   * @param name The name of the flag to search
   * @return true 
   * @return false 
   */
  bool GetFlag(const std::string& name) const;

  /**
   * @brief Returns true if the Parse method has been called
   * 
   * @return true 
   * @return false 
   */
  bool IsParsed() const;

 private:
  Cli();

  void ParseFlags(const std::vector<std::string>& pased_flags);
  
  void ParseArguments(const std::vector<std::string>& pased_arguments);

  void AddDefaultFlags();

  void ThrowUnexpectedFlagException(const std::string& unexpected_option);

  void ThrowParseException(const std::string& error_message);

  std::string binary_;
  std::vector<std::string> tokens_;

  std::string name_;
  std::vector<Argument> arguments_;
  std::vector<Flag> flags_;

  std::map<std::string, std::string> parsed_arguments_;
  std::vector<std::string> parsed_flags_;
  std::vector<std::string> overriding_flags_;

  bool is_parsed_;
};

}


#endif  //  LIB_UTILS_CLI_