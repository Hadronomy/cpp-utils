
#pragma once

#include <map>
#include <vector>
#include <functional>

namespace toffee {

/**
 * @brief Builds a map from an input map while getting the key from the key_func
 * and the value_func
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
inline std::map<TKey, TValue> BuildMap(const std::vector<TContent>& input_vector,
  std::function<TKey(TContent content)> key_func, 
  std::function<TValue(TContent content)> value_func) {
  std::map<TKey, TValue> output_map;
  for (TContent content : input_vector) {
    TKey new_key = key_func(content);
    TValue new_value = value_func(content);
    output_map[new_key] = new_value;
  }
  return output_map;
}

}
