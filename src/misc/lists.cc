/**
 * @file lists.cc
 * @author Pablo Hernández Jiménez (alu0101495934@ull.edu.es)
 * @brief 
 * @version 1.0
 * @date 2021-12-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <map>
#include <functional>
#include <vector>

#include "lists.h"

template<class TKey, class TValue, class TContent>
std::map<TKey, TValue> BuildMap(const std::vector<TContent>& input_vector, std::function<TKey(TContent content)> key_func, 
std::function<TValue(TContent content)> value_func) {
  std::map<TKey, TValue> output_map;
  for (TContent content : input_vector) {
    TKey new_key = key_func(content);
    TValue new_value = value_func(content);
    output_map[new_key] = new_value;
  }
  return output_map;
}