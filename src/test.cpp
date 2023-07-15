#include <smartmask/smartmask.hpp>

#include <iostream>
#include <bitset>

typedef smartmask::Mask<uint32_t, 31, 20, 0> TestMask;

int main()
{
  volatile uint32_t reg{0xff00ff00};
  std::cout << "reg before:\n" << std::bitset<32>{reg} << "\n";
  std::cout << "value before:\n" << TestMask::readFrom(reg) << "\n";
  TestMask::writeTo<0b011>(reg);
  std::cout << "reg after:\n" << std::bitset<32>{reg} << "\n";
  std::cout << "value after:\n" << TestMask::readFrom(reg) << "\n";
  return 0;
}