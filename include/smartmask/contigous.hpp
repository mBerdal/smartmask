#pragma once

#include <cstddef>
#include <cstdint>

namespace smartmask
{
template<typename Type, size_t MaxPos, size_t MinPos = MaxPos>
struct Contigous
{
  static constexpr Type ONE{static_cast<Type>(1)};
  static constexpr Type BITMASK{((ONE << (MaxPos + ONE)) - ONE) & ~((ONE << MinPos) - ONE)};
  static constexpr size_t MASKSIZE{1 + (MaxPos - MinPos)};

  template<Type Value>
  static void writeTo(volatile Type& dest)
  {
    static_assert(Value < (ONE << MASKSIZE));
    dest = (dest & ~BITMASK) | (Value << MinPos);
  }

  template<Type Value>
  static void writeTo(Type& dest)
  {
    static_assert(Value < (ONE << MASKSIZE));
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