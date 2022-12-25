
#pragma once

#include <limits>
#include <string>

namespace toffee {

struct DefaultType {
 public:
  template<typename T>
  operator T() const { return T(); }
};

const DefaultType kDefault = DefaultType();

/**
* @brief Returns true if the passed values overflows it's allowed size
* @tparam TNumeric
* @param value_to_check
* @return True if there's an overflow
*/
template<
  typename TNumeric,
  typename = typename std::enable_if<std::is_arithmetic<TNumeric>::value, TNumeric>::type
>
bool HasOverflow(const TNumeric& value_to_check) {
  return value_to_check >= std::numeric_limits<TNumeric>::max();
}

}  // namespace toffee
