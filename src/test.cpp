#include <smartmask/smartmask.hpp>

#include <iostream>
#include <bitset>


static constexpr smartmask::Mask<uint32_t, 31, 20, 0> MyMask1;
static constexpr smartmask::Mask<uint32_t, 19> MyMask2;

int main()
{
  volatile uint32_t reg{0xff00ff00u};
  std::cout << "reg before:\n" << std::bitset<32>{reg} << "\n";
  std::cout << "value before:\n" << MyMask1.readFrom(reg) << "\n";
  MyMask1.writeTo<0b011u>(reg);
  std::cout << "reg after template write:\n" << std::bitset<32>{reg} << "\n";
  std::cout << "value after template write:\n" << MyMask1.readFrom(reg) << "\n";
  MyMask1.writeTo(0b111u, reg);
  std::cout << "reg after non-template write:\n" << std::bitset<32>{reg} << "\n";
  std::cout << "value after non-template write:\n" << MyMask1.readFrom(reg) << "\n";

  MyMask2.writeTo<1>(reg);
  return 0;
}