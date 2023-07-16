#pragma once

#include <cstddef>
#include <cstdint>

namespace smartmask
{
template<typename Type, size_t BitPositionLeft, size_t... BitPositionsRight>
struct Mask
{
  static constexpr Type ONE{static_cast<Type>(1)};
  static constexpr Type BITMASK{(ONE << BitPositionLeft) | Mask<Type, BitPositionsRight...>::BITMASK};
  static constexpr size_t MASKSIZE{ONE + sizeof...(BitPositionsRight)};

  template<Type Value>
  static void writeTo(volatile Type& dest)
  {
    static_assert(Value < (ONE << MASKSIZE));
    dest = (dest & ~BITMASK) | distribute<Value>();
  }

  template<Type Value>
  static void writeTo(Type& dest)
  {
    static_assert(Value < (ONE << MASKSIZE));
    dest = (dest & ~BITMASK) | distribute<Value>();
  }

  static void writeTo(const Type value, Type& dest)
  {
    dest = (dest & ~BITMASK) | distribute(value);
  }
  static void writeTo(const Type value, volatile Type& dest)
  {
    dest = (dest & ~BITMASK) | distribute(value);
  }

  static Type readFrom(const Type src)
  {
    return (((src & (ONE << BitPositionLeft)) > 0) << (MASKSIZE - ONE)) | Mask<Type, BitPositionsRight...>::readFrom(src);
  }

  template<Type Value>  
  static Type distribute(void)
  {
    return (((Value & (ONE << (MASKSIZE - ONE))) > 0) << BitPositionLeft) | Mask<Type, BitPositionsRight...>::template distribute<Value>();
  }
  static Type distribute(const Type value)
  {
    return (((value & (ONE << (MASKSIZE - ONE))) > 0) << BitPositionLeft) | Mask<Type, BitPositionsRight...>::distribute(value);
  }
};

template<typename Type, size_t BitPosition>
struct Mask<Type, BitPosition>
{
  static constexpr Type ONE{static_cast<Type>(1)};
  static constexpr Type BITMASK{ONE << BitPosition};
  static constexpr Type MASKSIZE{ONE};

  template<Type Value>
  static void writeTo(volatile Type& dest)
  {
    static_assert(Value < (ONE << MASKSIZE));
    dest = (dest & ~BITMASK) | distribute<Value>();
  }

  template<Type Value>
  static void writeTo(Type& dest)
  {
    static_assert(Value < (ONE << MASKSIZE));
    dest = (dest & ~BITMASK) | distribute<Value>();
  }

  static void writeTo(const Type value, Type& dest)
  {
    dest = (dest & ~BITMASK) | distribute(value);
  }
  static void writeTo(const Type value, volatile Type& dest)
  {
    dest = (dest & ~BITMASK) | distribute(value);
  }

  static Type readFrom(const Type src) { return (src & (ONE << BitPosition)) > 0; }
  
  template<Type Value>
  static Type distribute(void) { return ((Value & ONE) > 0) << BitPosition; }
  static Type distribute(const Type value) { return ((value & ONE) > 0) << BitPosition; }
};
  
} // namespace smartmask

