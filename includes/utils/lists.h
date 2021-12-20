/**
 * @file lists.h
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LIB_UTILS_LISTS_
#define LIB_UTILS_LISTS_

#include <map>
#include <vector>
#include <functional>

namespace utils {

/**
 * @brief Builds a map from an input map while getting the key from the %key_func
 * and the %value_func
 * 
 * @tparam TKey 
 * @tparam TValue 
 * @tparam TContent 
 * @param input_vector 
 * @param key_func 
 * @param value_func 
 * @return std::map<TKey, TValue> 
 */
template<class TKey, class TValue, class TContent>
std::map<TKey, TValue> BuildMap(const std::vector<TContent>& input_vector, 
  std::function<TKey(TContent content)> key_func, 
  std::function<TValue(TContent content)> value_func);

}

#endif  //  !LIB_UTILS_LISTS_