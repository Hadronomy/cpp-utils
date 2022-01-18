/**
 * @file primitive.h
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LIB_UTILS_CONSTEXPR_
#define LIB_UTILS_CONSTEXPR_

#include <type_traits>

namespace utils {

template<class TTest>
struct is_standard {
  static constexpr bool value = std::is_fundamental<TTest>::value || std::is_same<TTest, std::string>::value;
};

}

#endif  //  !LIB_UTILS_CONSTEXPR_