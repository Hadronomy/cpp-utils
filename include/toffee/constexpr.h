
#pragma once

#include <type_traits>
#include <string>

namespace toffee {

template<class TTest>
struct IsStandard {
  static constexpr bool value = std::is_fundamental<TTest>::value || std::is_same<TTest, std::string>::value;
};

}
