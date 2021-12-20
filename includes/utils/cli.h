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

#include "cli/command.h"
#include "cli/argument.h"
#include "cli/flag.h"

namespace utils {

/**
 * @brief Utility class to manage cli argument parsing
 * 
 */
class Cli : Command {
 public:
  Cli(std::string name, std::string description, std::vector<Argument> arguments, std::vector<Argument> options, std::vector<Flag> flags) :
    Command(name, description, arguments, options, flags) { }
  Cli(std::string name, std::string description, std::vector<Argument> arguments, std::vector<Argument> options) :
    Command(name, description, arguments, options) { }
  Cli(std::string name, std::string description, std::vector<Argument> arguments, std::vector<Flag> flags) : 
    Command(name, description, arguments, flags) { }
  Cli(std::string name, std::string description, std::vector<Argument> arguments) : 
    Command(name, description, arguments) { }
  Cli(std::string name, std::string description) :
    Command(name, description) { }

  void Parse(const int arg_count, char* pased_args[]);

  using Command::GetArgument;
};

}


#endif  //  LIB_UTILS_CLI_