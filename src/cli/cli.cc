/**
 * @file cli.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <exception>

#include "cli.h"
#include "colors.h"
#include "misc/exceptions.h"

namespace utils {

void Cli::Parse(const int &argument_count, char* arguments[]) {
  binary_ = arguments[0];
  AddDefaultFlags();
  for (int current_arg = 1; current_arg < argument_count; ++current_arg) {
    tokens_.push_back(std::string(arguments[current_arg]));
  }
  std::vector<std::string> pased_flags;
  std::vector<std::string> pased_arguments;
  for (auto token : tokens_) {
    if (token[0] == '-' && token[1] != '-') {
      pased_flags.push_back(token.substr(1, token.size() - 1));
    } else if (token.substr(0, 2) == "--") {
      pased_flags.push_back(token.substr(2, token.size() - 1));
    } else {
      pased_arguments.push_back(token);
    }
  }
  ParseFlags(pased_flags);
  ParseArguments(pased_arguments);
  is_parsed_ = true;
}

void Cli::AddDefaultFlags() {
  Flag help("help", "h", "Shows the command information", true);
  Flag verbose("verbose", "v", "Explains whats being done", false);
  flags_.push_back(help);
  flags_.push_back(verbose);
  return;
}

void Cli::ParseFlags(const std::vector<std::string>& pased_flags) {
  if (pased_flags.size() > flags_.size()) {
    ThrowParseException("More flags than expected");
  }
  for (auto pased_flag : pased_flags) {
    bool is_expected_flag = false;
    for (auto expected_flag : flags_) {
      if (expected_flag.GetName() == pased_flag || expected_flag.GetAlias() == pased_flag ) {
        parsed_flags_.push_back(expected_flag.GetName());
        if (pased_flag == "help") {
          ShowHelp();
        }
        if (expected_flag.IsOverriding()) {
          overriding_flags_.push_back(expected_flag.GetName());
        }
        is_expected_flag = true;
      }
    }
    if (!is_expected_flag) {
      ThrowUnexpectedFlagException(pased_flag);
    }
    if (overriding_flags_.size() > 0) {
      exit(EXIT_SUCCESS);
    }
  }
}

void Cli::ParseArguments(const std::vector<std::string>& pased_arguments) {
  if (arguments_.size() < pased_arguments.size()) {
    ThrowParseException("More arguments than expected");
  } else if (arguments_.size() > pased_arguments.size()) {
    ThrowParseException("Less arguments than expected");
  }
  int argument_index = 0;
  for (auto pased_argument : pased_arguments) {
    parsed_arguments_[arguments_[argument_index].GetName()] = pased_argument;
    ++argument_index;
  }
  return;
}

bool Cli::GetFlag(const std::string& flag_name) const {
  if (!is_parsed_) {
    ThrowParseException("Getting flag before parsing");
  }
  for (auto parsed_flag : parsed_flags_) {
    if (parsed_flag == flag_name) {
      return true;
    }
  }
  return false;
}

std::string Cli::GetArgument(const std::string& argument_name) const {
  if (!is_parsed_) {
    ThrowParseException("Getting argument before parsing");
  }
  return parsed_arguments_.at(argument_name);
}

void Cli::ShowHelp() const {
  std::cout << utils::Colorize(utils::FontStyle::kBold);
  std::cout << name_ << " v1.0.0" << std::endl;
  std::cout << std::endl;
  std::cout << description_ << std::endl;
  std::cout << std::endl;
  std::cout << utils::Colorize(utils::FontStyle::kBold);
  std::cout << utils::Colorize(utils::FontStyle::kUnderline);
  std::cout << "Usage" << std::endl;
  std::cout << utils::Colorize::Reset;
  std::cout << "  " << binary_ << " [flags]";
  for (auto argument : arguments_) {
    std::cout << " <" << argument.GetName() << ">";
  }
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << utils::Colorize(utils::FontStyle::kUnderline) << utils::Colorize(utils::FontStyle::kBold);
  std::cout << "Arguments" << utils::Colorize::Reset << std::endl;
  for (auto argument : arguments_) {
    std::cout << utils::Colorize(utils::FontStyle::kBold);
    std::cout << "  " << argument.GetName() << ": ";
    std::cout << utils::Colorize::Reset;
    std::cout << argument.GetDescription() << std::endl;
  }
  std::cout << std::endl;
  std::cout << utils::Colorize(utils::FontStyle::kUnderline) << utils::Colorize(utils::FontStyle::kBold);
  std::cout << "Flags" << utils::Colorize::Reset << std::endl;
  for (auto flag : flags_) {
    std::cout << utils::Colorize(utils::FontStyle::kBold);
    std::cout << "  " << "--" << flag.GetName() << " " <<  "-" << flag.GetAlias() << ": ";
    std::cout << utils::Colorize::Reset;
    std::cout << flag.GetDescription() << std::endl;
  }
}

void Cli::ThrowUnexpectedFlagException(const std::string& unexpected_flag) const {
  std::cerr << utils::Colorize(utils::ColorTint::kRed) << utils::Colorize(utils::FontStyle::kBold);
  std::cerr << "Unexpected " << unexpected_flag << " flag" << utils::Colorize::Reset << std::endl;
  std::cerr << "Try " << binary_ << " --help to see the expected flags" << std::endl;
  exit(EXIT_FAILURE);
}

void Cli::ThrowParseException(const std::string& error_message) const {
  std::cerr << utils::Colorize(utils::ColorTint::kRed) << utils::Colorize(utils::FontStyle::kBold);
  std::cerr << error_message << utils::Colorize::Reset << std::endl;
  std::cerr << "Try " << binary_ << " --help to learn about the correct use of this command" << std::endl;
  exit(EXIT_FAILURE);
}

}