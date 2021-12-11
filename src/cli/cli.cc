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

#include "utils/cli.h"
#include "utils/colors.h"
#include "misc/exceptions.h"

namespace utils {

void Cli::Parse(const int &argument_count, char* arguments[]) {
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
  if (pased_flags.size() > options_.size()) {
    ThrowParseException("More options than expected");
  }
  bool option_override = false;
  for (auto pased_flag : pased_flags) {
    bool is_expected_option = false;
    for (auto expected_option : options_) {
      if (expected_option.GetName() == pased_flag || expected_option.GetAlias() == pased_flag ) {
        parsed_options_.push_back(expected_option.GetName());
        // TODO: Improve option override
        if (expected_option.GetName() == "help") {
          option_override = true;
        }
        is_expected_option = true;
      }
    }
    if (!is_expected_option) {
      ThrowUnexpectedOptionException(pased_flag);
    }
  }
  if (option_override) {
    return;
  }
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

bool Cli::GetFlag(const std::string& option_name) {
  for (auto parsed_option : parsed_options_) {
    if (parsed_option == option_name) {
      return true;
    }
  }
  return false;
}

std::string Cli::GetArgument(const std::string& argument_name) {
  return parsed_arguments_[argument_name];
}

void Cli::ShowHelp() {
  std::cout << utils::Colorize(utils::FontStyle::kBold);
  std::cout << name_ << " v1.0.0" << std::endl;
  std::cout << std::endl;
  std::cout << utils::Colorize(utils::FontStyle::kBold);
  std::cout << utils::Colorize(utils::FontStyle::kUnderline);
  std::cout << "Usage" << std::endl;
  std::cout << utils::Colorize::Reset;
  std::cout << "  " << name_ << " [options]" << " <arguments>" << std::endl;
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
  std::cout << "Options" << utils::Colorize::Reset << std::endl;
  for (auto option : options_) {
    std::cout << utils::Colorize(utils::FontStyle::kBold);
    std::cout << "  " << "--" << option.GetName() << " " <<  "-" << option.GetAlias() << ": ";
    std::cout << utils::Colorize::Reset;
    std::cout << option.GetDescription() << std::endl;
  }
}

void Cli::ThrowUnexpectedOptionException(const std::string& unexpected_option) {
  std::cerr << utils::Colorize(utils::ColorTint::kRed) << utils::Colorize(utils::FontStyle::kBold);
  std::cerr << "Unexpected " << unexpected_option << " option" << utils::Colorize::Reset << std::endl;
  std::cerr << "--help to see the expected options" << std::endl;
  throw "Unexpected";
}

void Cli::ThrowParseException(const std::string& error_message) {
  std::cerr << utils::Colorize(utils::ColorTint::kRed) << utils::Colorize(utils::FontStyle::kBold);
  std::cerr << error_message << utils::Colorize::Reset << std::endl;
  std::cerr << "--help to see learn about the correct use of this command" << std::endl;
  throw ParseException(error_message);
}

}