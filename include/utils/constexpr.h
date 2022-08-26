/**
 * @file primitive.h
 * @author Pablo Hernández Jiménez
 * @brief 
 * @version 1.0
 * @date 2021-12-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <type_traits>
#include <string>

namespace utils {

template<typename TTest>
struct is_standard {
  static constexpr bool value = std::is_fundamental<TTest>::value || std::is_same<TTest, std::string>::value;
};

/**
 * @brief
 * Repeats the process of shifting and copying the
 * given bits an specified amount of times
 * @tparam TInt
 * @param initial The bits to shift and copy
 * @param amount The amount of times to shift and copy
 * @example
 * ShiftCopyBit<uint8_t>(1, 4) => 0x00001111;
 * @return
 */
template<typename TInt>
constexpr TInt ShiftCopyBit(TInt initial, size_t amount) {
  for (int i = 0; i < amount; initial |= initial << i, ++i);
  return initial;
}

}
