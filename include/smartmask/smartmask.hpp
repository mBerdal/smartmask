#pragma once

#include <cstddef>
#include <cstdint>

namespace smartmask
{
template<typename Type, size_t BitPositionLeft, size_t... BitPositionsRight>
struct Mask
{
  static constexpr Type BITMASK{(1 << BitPositionLeft) | Mask<Type, BitPositionsRight...>::BITMASK};
  static constexpr size_t MASKSIZE{1 + Mask<Type, BitPositionsRight...>::MASKSIZE};

  template<Type Value>
  static void writeTo(volatile Type& dest)
  {
    static_assert(Value < (1 << MASKSIZE));
    dest = (dest & ~BITMASK) | distribute<Value>();
  }

  template<Type Value>
  static void writeTo(Type& dest)
  {
    static_assert(Value < (1 << MASKSIZE));
    dest = (dest & ~BITMASK) | distribute<Value>();
  }

  static Type readFrom(const Type src)
  {
    return (((src & (1 << BitPositionLeft)) > 0) << (MASKSIZE - 1)) | Mask<Type, BitPositionsRight...>::readFrom(src);
  }

  template<Type Value>  
  static Type distribute(void)
  {
    return (((Value & (1 << (MASKSIZE - 1))) > 0) << BitPositionLeft) | Mask<Type, BitPositionsRight...>::template distribute<Value>();
  }
};

template<typename Type, size_t BitPosition>
struct Mask<Type, BitPosition>
{
  static constexpr Type BITMASK{1 << BitPosition};
  static constexpr size_t MASKSIZE{1};

  template<Type Value>
  static Type distribute(void) { return ((Value & 1) > 0) << BitPosition; }

  static Type readFrom(const Type src) { return (src & (1 << BitPosition)) > 0; }
};
  
} // namespace smartmask

