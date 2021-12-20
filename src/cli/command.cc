/**
 * @file command.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>

#include "colors.h"
#include "command.h"
#include "constexpr.h"

namespace utils {

void Command::CreateLookup() {
  for (auto flag : flags_) {
    lookup_flags_[flag.GetName()] = flag;
    lookup_flags_[flag.GetAlias()] = flag;
  }
  for (auto option : options_) {
    lookup_options_[option.GetName()] = option;
  }
  return;
}

void Command::AddDefaults() {
  flags_.push_back(utils::Flag("help", "h" "Show detailed information about the use of the utility", true));
  flags_.push_back(utils::Flag("verbose", "v", "Print to the stderr what's being done", false));
  return;
}

bool Command::IsFlag(const std::string& token, std::string& name) {
  if (token[0] == '-' && token[1] != '-' && !std::isdigit(token[1]) && std::isalpha(token[1])) {
    name = token.substr(1);
    return true;
  } else if (token.substr(0, 2) == "--") {
    name = token.substr(2);
    return true;
  }
  return false;
}

bool Command::IsOption(const std::string& token, std::string& name) {
  if (token.substr(0, 2) == "--") {
    name = token.substr(2);
    return true;
  }
  return false;
}

void Command::ParseCommand(const int arg_count, char* provided_args[]) {
  AddDefaults();
  CreateLookup();
  for (int current_arg = 1; current_arg < arg_count; ++current_arg) {
    args_.push(std::string(provided_args[current_arg]));
  }
  int position_argument_index = 0;
  while (!args_.empty()) {
    std::string current_argument = args_.front();
    std::string name;
    bool is_flag = IsFlag(current_argument, name);
    if (is_flag && lookup_flags_.count(name) > 0) {
      if (name == "help"  || name == "h") {
        ShowHelp();
        exit(EXIT_SUCCESS);
      }
      parsed_flags_[name] = "true";
      args_.pop();
      if (lookup_flags_[name].GetIsOverriding()) {
        break;
      }
      continue;
    } else if (IsOption(current_argument, name) && lookup_options_.count(name) == 0) {
      ThrowUnexpectedFlagException(current_argument);
    }
    bool is_option = IsOption(current_argument, name);
    if (is_option && lookup_options_.count(name)) {
      // TODO: Check if empty
      args_.pop();
      std::string value = args_.front();
      parsed_options_[name] = value;
      args_.pop();
      continue;
    } else if (is_option) {
      std::string error_message = "Unexpected " + current_argument + " option";
      ThrowParseException(error_message);
    }
    if (position_argument_index >= arguments_.size()) {
      ThrowParseException("More arguments than expected");
    }
    std::string positional_argument_name = arguments_[position_argument_index].GetName();
    parsed_arguments_[positional_argument_name] = args_.front();
    ++position_argument_index;
    args_.pop();
  }
  if (position_argument_index < arguments_.size()) {
    ThrowParseException("Less arguments than expected");
  }
  SetParsed(true);
}

void Command::ShowHelp() const {
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

void Command::ThrowUnexpectedFlagException(const std::string& unexpected_flag) const {
  std::cerr << utils::Colorize(utils::ColorTint::kRed) << utils::Colorize(utils::FontStyle::kBold);
  std::cerr << "Unexpected " << unexpected_flag << " flag" << utils::Colorize::Reset << std::endl;
  std::cerr << "Try " << binary_ << " --help to see the expected flags" << std::endl;
  exit(EXIT_FAILURE);
}

void Command::ThrowParseException(const std::string& error_message) const {
  std::cerr << utils::Colorize(utils::ColorTint::kRed) << utils::Colorize(utils::FontStyle::kBold);
  std::cerr << error_message << utils::Colorize::Reset << std::endl;
  std::cerr << "Try " << binary_ << " --help to learn about the correct use of this command" << std::endl;
  exit(EXIT_FAILURE);
}

}