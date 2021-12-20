/**
 * @file token.h
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>

#ifndef LIB_UTILS_TOKEN_
#define LIB_UTILS_TOKEN_

class Token {
 public:
  bool GetIsOverriding() {
    return is_overriding;
  }
 protected:
  std::string name_;
  std::string description_;
  bool is_overriding;
};

#endif  //  !LIB_UTILS_TOKEN_