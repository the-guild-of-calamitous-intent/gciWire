
#include "i2c.hpp"

TwoWire tw;

int main() {
  SensorI2C sen(&tw, 0x33);
  return 0;
}
