#include <smartmask/smartmask.hpp>

#include <iostream>
#include <bitset>

typedef smartmask::Mask<uint32_t, 31, 20, 0> TestMask;

static constexpr smartmask::Mask<uint32_t, 31, 20, 0> MyMask;

int main()
{
  volatile uint32_t reg{0xff00ff00u};
  std::cout << "reg before:\n" << std::bitset<32>{reg} << "\n";
  std::cout << "value before:\n" << MyMask.readFrom(reg) << "\n";
  MyMask.writeTo<0b011u>(reg);
  std::cout << "reg after template write:\n" << std::bitset<32>{reg} << "\n";
  std::cout << "value after template write:\n" << MyMask.readFrom(reg) << "\n";
  MyMask.writeTo(0b111u, reg);
  std::cout << "reg after non-template write:\n" << std::bitset<32>{reg} << "\n";
  std::cout << "value after non-template write:\n" << MyMask.readFrom(reg) << "\n";
  return 0;
}