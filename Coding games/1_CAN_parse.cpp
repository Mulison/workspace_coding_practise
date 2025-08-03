#include <cstdint>
#include <iostream>

struct CanFrame {
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8];
};

uint16_t parseSpeed(const CanFrame& frame)
{
  uint16_t result = 0;
  result = frame.data[2] * 256 + frame.data[3];
  return result;
}

int main()
{
  CanFrame frame;
  frame.id = 0x100;
  frame.dlc = 8;
  frame.data[2] = 0x12;
  frame.data[3] = 0x34;
  auto speed = parseSpeed(frame);
  std::cout<< "++++++" << speed << std::endl;

}