#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>

namespace smartmask
{
template<typename Type, size_t MaxPos, size_t MinPos = MaxPos>
struct Contigous
{
  static constexpr Type ONE{static_cast<Type>(1)};
  static constexpr Type BITMASK{((MaxPos + 1 >= sizeof(Type) * 8) ? std::numeric_limits<Type>::max() : ((ONE << (MaxPos + ONE)) - ONE)) & ~((ONE << MinPos) - ONE)};
  static constexpr size_t MASKSIZE{1 + (MaxPos - MinPos)};
  static constexpr Type MAX_VALUE{MASKSIZE >= sizeof(Type) * 8 ? std::numeric_limits<Type>::max() : (ONE << MASKSIZE) - 1};

  template<Type Value>
  static void writeTo(volatile Type& dest)
  {
    static_assert(Value <= MAX_VALUE);
    dest = (dest & ~BITMASK) | (Value << MinPos);
  }

  template<Type Value>
  static void writeTo(Type& dest)
  {
    static_assert(Value <= MAX_VALUE);
    dest = (dest & ~BITMASK) | (Value << MinPos);
  }

  static void writeTo(const Type value, Type& dest)
  {
    dest = (dest & ~BITMASK) | (value << MinPos);
  }
  static void writeTo(const Type value, volatile Type& dest)
  {
    dest = (dest & ~BITMASK) | (value << MinPos);
  }

  static Type readFrom(const Type src)
  {
    return (src & BITMASK) >> MinPos;
  }
};

} // namespace smartmask