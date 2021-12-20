/**
 * @file command.h
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LIB_UTILS_COMMAND_
#define LIB_UTILS_COMMAND_

#include <string>
#include <vector>
#include <queue>
#include <map>
#include <type_traits>
#include <sstream>

#include "flag.h"
#include "argument.h"
#include "constexpr.h"

namespace utils
{

  class Command
  {
  public:
    Command(std::string name, std::string description, std::vector<Argument> arguments, std::vector<Argument> options, std::vector<Flag> flags) :
      name_(name), description_(description), arguments_(arguments), options_(options), flags_(flags) { }
    Command(std::string name, std::string description, std::vector<Argument> arguments, std::vector<Argument> options) :
      name_(name), description_(description), arguments_(arguments), options_(options) { }
    Command(std::string name, std::string description, std::vector<Argument> arguments, std::vector<Flag> flags) : 
      name_(name), description_(description), arguments_(arguments), flags_(flags) { }
    Command(std::string name, std::string description, std::vector<Argument> arguments) : 
      name_(name), description_(description), arguments_(arguments) { }
    Command(std::string name, std::string description) : 
      name_(name), description_(description) { }

    void ParseCommand(const int arg_count, char *provided_args[]);

    void ShowHelp() const;

    template <typename TReturn>
    inline TReturn GetArgument(const std::string& argument_name) const {
      return GetTypedFromList<TReturn>(parsed_arguments_, argument_name);
    }

    template <typename TReturn>
    inline TReturn GetOption(const std::string& option_name) const {
      return GetTypedFromList<TReturn>(parsed_options_, option_name);
    }

    template <typename TReturn>
    inline TReturn GetTypedFromList(const std::map<std::string, std::string>& list, const std::string& key) const {
      static_assert(utils::is_standard<TReturn>::value, "Return type must be a primitive type or a string");
      std::string argument = list.at(key);
      if (std::is_same<TReturn, std::string>::value) {
        std::stringstream value_string(argument);
        TReturn value;
        value_string >> value;
        return value;
      }
      else if (std::is_arithmetic<TReturn>::value) {
        std::stringstream value_string(argument);
        TReturn value;
        value_string >> value;
        return value;
      }
    }

    inline bool GetFlag(const std::string& flag_name) const {
      return parsed_flags_.count(flag_name) > 0;
    }

    inline void SetBinary(const std::string& binary) {
      binary_ = binary;
    }

    inline void SetParsed(const bool parse_state) {
      is_parsed_ = parse_state;
    }

  protected:
    std::string name_;
    std::string description_;
    std::vector<Argument> arguments_;
    std::vector<Argument> options_;
    std::vector<Flag> flags_;

    std::string binary_;
    bool is_parsed_ = false;

    std::map<std::string, Token> lookup_flags_;
    std::map<std::string, Token> lookup_options_;

    std::queue<std::string> args_;

    std::map<std::string, std::string> parsed_arguments_;
    std::map<std::string, std::string> parsed_options_;
    std::map<std::string, std::string> parsed_flags_;

    void CreateLookup();

    void AddDefaults();

    bool IsOption(const std::string &token, std::string &name);

    bool IsFlag(const std::string &token, std::string &name);

    void ThrowUnexpectedFlagException(const std::string &unexpected_flag) const;

    void ThrowParseException(const std::string &error_message) const;
  };

}

#endif //  !LIB_UTILS_COMMAND_