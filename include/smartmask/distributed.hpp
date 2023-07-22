#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>

namespace smartmask
{
template<typename Type, size_t BitPositionLeft, size_t... BitPositionsRight>
struct Distributed
{
  static constexpr Type ONE{static_cast<Type>(1)};
  static constexpr Type BITMASK{(ONE << BitPositionLeft) | Distributed<Type, BitPositionsRight...>::BITMASK};
  static constexpr size_t MASKSIZE{ONE + sizeof...(BitPositionsRight)};
  static constexpr Type MAX_VALUE{MASKSIZE == sizeof(Type) * 8 ? std::numeric_limits<Type>::max() : (ONE << MASKSIZE) - 1};
  static_assert(MASKSIZE <= sizeof(Type) * 8);

  template<Type Value>
  static void writeTo(volatile Type& dest)
  {
    static_assert(Value <= MAX_VALUE);
    dest = (dest & ~BITMASK) | distribute<Value>();
  }

  template<Type Value>
  static void writeTo(Type& dest)
  {
    static_assert(Value <= MAX_VALUE);
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
    return (((src & (ONE << BitPositionLeft)) > 0) << (MASKSIZE - ONE)) | Distributed<Type, BitPositionsRight...>::readFrom(src);
  }

  template<Type Value>  
  static Type distribute(void)
  {
    return (((Value & (ONE << (MASKSIZE - ONE))) > 0) << BitPositionLeft) | Distributed<Type, BitPositionsRight...>::template distribute<Value>();
  }
  static Type distribute(const Type value)
  {
    return (((value & (ONE << (MASKSIZE - ONE))) > 0) << BitPositionLeft) | Distributed<Type, BitPositionsRight...>::distribute(value);
  }
};

template<typename Type, size_t BitPosition>
struct Distributed<Type, BitPosition>
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

