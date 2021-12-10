/**
 * @file exceptions.h
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#ifndef LIB_UTILS_EXCEPTIONS_
#define LIB_UTILS_EXCEPTIONS_

#include <exception>
#include <string>

/**
 * @brief Cli parse exception
 *
 */
class ParseException : public std::exception {
 public:
  ParseException(const std::string& error_message) {
    error_message_ = error_message;
  }
  virtual const char* what() const throw() {
    return error_message_.data();
  }
 private:
  std::string error_message_;
};

#endif  //  !LIB_UTILS_EXCEPTIONS_