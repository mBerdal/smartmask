#include <smartmask/distributed.hpp>
#include <smartmask/contigous.hpp>

#include <iostream>
#include <bitset>


static constexpr smartmask::Distributed<uint32_t, 31, 20, 0> MyMask1;
static constexpr smartmask::Contigous<uint32_t, 2, 1> MyMask2;
static constexpr smartmask::Contigous<uint32_t, 3> MyMask3;

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

  std::cout << "-------------------------" << std::endl;

  std::cout << "reg before:\n" << std::bitset<32>{reg} << "\n";
  std::cout << "value before:\n" << MyMask2.readFrom(reg) << "\n";
  MyMask2.writeTo<0b11u>(reg);
  std::cout << "reg after template write:\n" << std::bitset<32>{reg} << "\n";
  std::cout << "value after template write:\n" << MyMask2.readFrom(reg) << "\n";
  MyMask2.writeTo(0b111u, reg);
  std::cout << "reg after non-template write:\n" << std::bitset<32>{reg} << "\n";
  std::cout << "value after non-template write:\n" << MyMask2.readFrom(reg) << "\n";

  std::cout << "-------------------------" << std::endl;

  std::cout << "reg before:\n" << std::bitset<32>{reg} << "\n";
  std::cout << "value before:\n" << MyMask3.readFrom(reg) << "\n";
  MyMask3.writeTo<0b1>(reg);
  std::cout << "reg after template write:\n" << std::bitset<32>{reg} << "\n";
  std::cout << "value after template write:\n" << MyMask3.readFrom(reg) << "\n";
  MyMask3.writeTo(0b0, reg);
  std::cout << "reg after non-template write:\n" << std::bitset<32>{reg} << "\n";
  std::cout << "value after non-template write:\n" << MyMask3.readFrom(reg) << "\n";


  return 0;
}