
#pragma once

#include <type_traits>
#include <numeric>
#include <initializer_list>
#include <utility>

namespace toffee {

template<class TEnum>
class Flags {
 public:
  using EnumType = typename std::decay<TEnum>::type;
  using UnderlayingType = typename std::underlying_type<TEnum>::type;
  using ImplicitType = typename std::make_unsigned<UnderlayingType>::type;
  using SizeType = std::size_t;

  Flags() noexcept = default;

  constexpr Flags(EnumType e) noexcept
          : value_(static_cast<ImplicitType>(e)) {}

  // constexpr operator EnumType() const noexcept { return static_cast<EnumType>(value_); }
  constexpr explicit operator bool() const noexcept { return value_ != 0; }

  Flags& operator |=(const Flags& flags) noexcept {
    value_ |= flags.value_;
    return static_cast<Flags&>(*this);
  }

  Flags& operator &=(const Flags& flags) noexcept {
    value_ &= flags.value_;
    return static_cast<Flags&>(*this);
  }

  Flags& operator ^=(const Flags& flags) noexcept {
    value_ ^= flags.value_;
    return static_cast<Flags&>(*this);
  }

  friend constexpr Flags operator|(const Flags& left, const Flags& right) {
    return Flags(static_cast<ImplicitType>(left.value_ | right.value_));
  }

  friend constexpr Flags operator&(const Flags& left, const Flags& right) {
    return Flags(static_cast<ImplicitType>(left.value_ & right.value_));
  }

  friend constexpr Flags operator^(const Flags& left, const Flags& right) {
    return Flags(static_cast<ImplicitType>(left.value_ ^ right.value_));
  }

  friend constexpr Flags operator~(const Flags& flag) {
    return Flags(static_cast<ImplicitType>(~flag.value_));
  }

 private:
  constexpr explicit Flags(ImplicitType value) noexcept
          : value_(value) {}

  ImplicitType value_;
};

}

// TODO: Check if this can be inside the namespace

template<class TEnum>
constexpr auto operator |(TEnum left, TEnum right) noexcept {
  return toffee::Flags<TEnum>(left) | right;
}

template<class TEnum>
constexpr auto operator &(TEnum left, TEnum right) noexcept {
  return toffee::Flags<TEnum>(left) & right;
}

template<class TEnum>
constexpr auto operator ^(TEnum left, TEnum right) noexcept {
  return toffee::Flags<TEnum>(left) ^ right;
}

template<class TEnum>
constexpr auto operator ~(TEnum enumerator) noexcept {
  return ~toffee::Flags<TEnum>(enumerator);
}
